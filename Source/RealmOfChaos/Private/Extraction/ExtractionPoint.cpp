// Fill out your copyright notice in the Description page of Project Settings.


#include "Extraction/ExtractionPoint.h"

#include "Components/ShapeComponent.h"

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

	if (OtherActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is in %s"), *OtherActor->GetName(), *PointName.ToString());
	}
}

// Called every frame
void AExtractionPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

