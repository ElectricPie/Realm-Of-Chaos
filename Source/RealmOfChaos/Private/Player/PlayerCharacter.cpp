// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/InventoryComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Items/ItemActor.h"
#include "Kismet/GameplayStatics.h"

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

	GroundItemsDetectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Ground Items Detection Sphere"));
	GroundItemsDetectionSphere->SetupAttachment(RootComponent);
	GroundItemsDetectionSphere->SetSphereRadius(400.f);
	GroundItemsDetectionSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory Component"));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		GroundItemsDetectionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
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

void APlayerCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (AItemActor* Item = Cast<AItemActor>(OtherActor))
	{
		NearbyItems.Add(Item);
		OnItemNearbyEvent.Broadcast(NearbyItems);
	}
}

void APlayerCharacter::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	
	if (AItemActor* Item = Cast<AItemActor>(OtherActor))
	{
		NearbyItems.Remove(Item);
		OnItemNearbyEvent.Broadcast(NearbyItems);
	}
}


void APlayerCharacter::Move(const FVector Direction)
{
	// Reduce the players speed if they are moving backwards
	float ForwardSpeedModifier = 1.f;
	if (!IsMovingForward())
	{
		ForwardSpeedModifier = BackwardsSpeedModifier;
	}
	
	// Move the character in the direction of the input using the world space direction
	AddMovementInput(FVector::ForwardVector, Direction.X * SpeedModifier * ForwardSpeedModifier);
	AddMovementInput(FVector::RightVector, Direction.Y * SpeedModifier * ForwardSpeedModifier);
}

bool APlayerCharacter::IsMovingForward() const
{
	const FVector ForwardVector = GetActorForwardVector();
	const FVector Velocity = GetVelocity().GetSafeNormal();

	const float DotProduct = FVector::DotProduct(ForwardVector, Velocity);
	return DotProduct > BackwardsThreshold;
}