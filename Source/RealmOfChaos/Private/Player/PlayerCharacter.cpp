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

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision Capsule"));
	RootComponent = Capsule;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;
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
	Direction = FRotator(0.f, RotationOffset, 0.f).RotateVector(Direction);

	// Prevent the character from looking up or down
	Direction.Z = 0.f;

	const FRotator NewRotation = Direction.Rotation();
	SetActorRotation(NewRotation);

	// Update the server
	if (Controller && Controller->GetLocalRole() == ROLE_AutonomousProxy)
	{
		ServerUpdateRotation(GetActorRotation());
	}
}
