// Fill out your copyright notice in the Description page of Project Settings.


#include "Extraction/ExtractionPoint.h"

#include "Components/ShapeComponent.h"
#include "GameModes/ExtractionGameMode.h"
#include "Player/TopDownPlayerController.h"

// Sets default values
AExtractionPoint::AExtractionPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void AExtractionPoint::BeginPlay()
{
	Super::BeginPlay();

	if (!GetComponentByClass<UShapeComponent>())
	{
		UE_LOG(LogTemp, Error, TEXT("%s is missing collision component"), *GetActorNameOrLabel());
	}
}

void AExtractionPoint::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (!HasAuthority()) return;

	ATopDownPlayerController* PlayerController = Cast<ATopDownPlayerController>(OtherActor->GetOwner());
	if (!IsValid(PlayerController)) return;
	
	AExtractionGameMode* GameMode = Cast<AExtractionGameMode>(GetWorld()->GetAuthGameMode());
	if (!IsValid(GameMode)) return;

	GameMode->StartPlayerExtraction(PlayerController, this);
	
}

void AExtractionPoint::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	ATopDownPlayerController* PlayerController = Cast<ATopDownPlayerController>(OtherActor->GetOwner());
	if (!IsValid(PlayerController)) return;
	
	AExtractionGameMode* GameMode = Cast<AExtractionGameMode>(GetWorld()->GetAuthGameMode());
	if (!IsValid(GameMode)) return;

	GameMode->CancelPlayerExtraction(PlayerController);
}

// Called every frame
void AExtractionPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

