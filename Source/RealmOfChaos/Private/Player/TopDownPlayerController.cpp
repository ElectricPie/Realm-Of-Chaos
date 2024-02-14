// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TopDownPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Net/UnrealNetwork.h"
#include "Player/PlayerCharacter.h"
#include "Extraction/ExtractionPoint.h"
#include "Ui/ExtractionPlayerHud.h"
#include "Ui/ExtractionPointListWidget.h"


void ATopDownPlayerController::AuthSetExtractionPoints(TArray<const AExtractionPoint*> NewExtractionPoints)
{
	if (!HasAuthority()) return;

	ExtractionPoints = NewExtractionPoints;

	if (IsLocalPlayerController())
	{
		OnRep_ExtractionPoints();
	}
}

void ATopDownPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Only run on the controlling clients
	if (!IsLocalPlayerController()) return;

	bShowMouseCursor = true;
	bReplicates = true;

	PlayerCharacter = Cast<APlayerCharacter>(GetPawn());

	// Set up input
	if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<
		UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		InputSubsystem->AddMappingContext(MappingContext, 0);
	}

	// Setup Ui
	if (ExtractionHudClass)
	{
		Hud = CreateWidget<UExtractionPlayerHud>(this, ExtractionHudClass);
		Hud->AddToViewport();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ExtractionHudClass is not set in %s"), *GetName());
	}

	// Setup extraction points hud update timer
	GetWorldTimerManager().SetTimer(ExtractionPointsHudUpdateTimer, this, &ATopDownPlayerController::UpdateExtractionPointsUI, ExtractionPointsHudUpdateInterval, true);
}

void ATopDownPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!IsValid(PlayerCharacter)) return;

	int32 ViewportSizeX;
	int32 ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	if (FVector2D MouseScreenLocation; GetMousePosition(MouseScreenLocation.X, MouseScreenLocation.Y))
	{
		FVector WorldPosition;
		FVector WorldDirection;
		DeprojectScreenPositionToWorld(MouseScreenLocation.X, MouseScreenLocation.Y, WorldPosition, WorldDirection);

		FHitResult HitResult;
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);

		if (GetWorld()->LineTraceSingleByChannel(HitResult, WorldPosition,
		                                         WorldPosition + WorldDirection * RaycastLimit, ECC_Visibility,
		                                         QueryParams))
		{
			DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 50.f, 8, FColor::Red);

			RotateToTarget(HitResult.ImpactPoint);
		}
	}

	// TODO: Debug remove when done
	for (auto& Point : ExtractionPoints)
	{
		DrawDebugLine(GetWorld(), PlayerCharacter->GetActorLocation(), Point->GetActorLocation(), FColor::Green);
	}
}

void ATopDownPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATopDownPlayerController::Move);
	}
}

void ATopDownPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATopDownPlayerController, ExtractionPoints);
}


void ATopDownPlayerController::Move(const FInputActionValue& Value)
{
	if (!PlayerCharacter) return;

	const FVector2d Dir = Value.Get<FVector2d>();
	// Use normal to prevent diagonal movement being faster
	PlayerCharacter->Move(FVector(Dir.X, Dir.Y, 0.f).GetSafeNormal());
}

void ATopDownPlayerController::RotateToTarget(FVector TargetLocation)
{
	if (IsValid(PlayerCharacter))
	{
		// Get the direction the character should face accounting for the meshes rotational offset
		FVector Direction = (TargetLocation - PlayerCharacter->GetActorLocation()).GetSafeNormal();
		// Prevent the character from looking up or down
		Direction.Z = 0.f;

		ClientSetRotation(Direction.Rotation());
	}
}

void ATopDownPlayerController::OnRep_ExtractionPoints()
{
	bResetPointUi = true;
}

void ATopDownPlayerController::UpdateExtractionPointsUI()
{
	if (!IsLocalPlayerController() && !Hud) return;

	UExtractionPointListWidget* ExtractionPointListWidget = Hud->GetExtractionPointListWidget();
	if (!ExtractionPointListWidget) return;

	if (bResetPointUi)
	{
		ExtractionPointListWidget->ClearExtractionPoints();
		for (const auto& Point : ExtractionPoints)
		{
			ExtractionPointListWidget->AddExtractionPoint(FText::FromName(Point->GetPointName()),
				FVector::Dist(PlayerCharacter->GetActorLocation(), Point->GetActorLocation()));
		}
		
		bResetPointUi = false;
	}
	
	// TODO: Update the extraction points list
}
