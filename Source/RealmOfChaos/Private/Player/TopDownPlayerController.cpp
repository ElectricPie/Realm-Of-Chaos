// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TopDownPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Player/PlayerCharacter.h"

void ATopDownPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;

	PlayerCharacter = Cast<APlayerCharacter>(GetPawn());

	if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		InputSubsystem->AddMappingContext(MappingContext, 0);
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

void ATopDownPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!IsValid(PlayerCharacter)) return;

	int32 ViewportSizeX;
	int32 ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	if (FVector2D MouseScreenLocation ; GetMousePosition(MouseScreenLocation.X, MouseScreenLocation.Y))
	{
		FVector WorldPosition;
		FVector WorldDirection;
		DeprojectScreenPositionToWorld(MouseScreenLocation.X, MouseScreenLocation.Y, WorldPosition, WorldDirection);

		FHitResult HitResult;
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);

		if (GetWorld()->LineTraceSingleByChannel(HitResult, WorldPosition,
			WorldPosition + WorldDirection * RaycastLimit, ECC_Visibility, QueryParams))
		{
			DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 50.f, 8, FColor::Red);

			PlayerCharacter->FaceDirection(HitResult.ImpactPoint);
		}
	}
}

void ATopDownPlayerController::Move(const FInputActionValue& Value)
{
	if (!PlayerCharacter) return;
	
	const FVector2d Dir = Value.Get<FVector2d>();
	// Use normal to prevent diagonal movement being faster
	PlayerCharacter->Move(FVector(Dir.X, Dir.Y, 0.f).GetSafeNormal());
}