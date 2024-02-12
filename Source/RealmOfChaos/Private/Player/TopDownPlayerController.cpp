// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TopDownPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Net/UnrealNetwork.h"
#include "Player/PlayerCharacter.h"
#include "Extraction/ExtractionPoint.h"


void ATopDownPlayerController::AuthSetExtractionPoints(TArray<const AExtractionPoint*> NewExtractionPoints)
{
	if (!HasAuthority()) return;

	ExtractionPoints = NewExtractionPoints;
}

void ATopDownPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;
	bReplicates = true;

	PlayerCharacter = Cast<APlayerCharacter>(GetPawn());

	if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<
		UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		InputSubsystem->AddMappingContext(MappingContext, 0);
	}
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