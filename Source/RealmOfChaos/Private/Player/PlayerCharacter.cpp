// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetUsingAbsoluteRotation(true);
	SpringArm->TargetArmLength = 1200.f;
	SpringArm->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	SpringArm->bDoCollisionTest = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerCharacter::ServerUpdateRotation_Implementation(FRotator NewRotation)
{
	SetActorRotation(NewRotation);
}

void APlayerCharacter::FaceDirection(const FVector LookTarget)
{
	// Get the direction the character should face accounting for the meshes rotational offset
	FVector Direction = (LookTarget - GetActorLocation()).GetSafeNormal();
	
	// Prevent the character from looking up or down
	Direction.Z = 0.f;

	const FRotator NewRotation = Direction.Rotation();
	SetActorRotation(NewRotation);

	// Update the server
	if (Controller && Controller->GetLocalRole() == ROLE_AutonomousProxy)
	{
		ServerUpdateRotation(NewRotation);
	}
}

void APlayerCharacter::Move(FVector Direction)
{
	// Move the character in the direction of the input using the world space direction
	AddMovementInput(FVector::ForwardVector, Direction.X);
	AddMovementInput(FVector::RightVector, Direction.Y);
}
