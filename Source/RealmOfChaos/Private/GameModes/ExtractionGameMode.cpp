// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/ExtractionGameMode.h"

#include "Extraction/ActiveExtractionPoints.h"
#include "Extraction/ExtractionPoint.h"
#include "Kismet/GameplayStatics.h"
#include "States/ExtractionGameState.h"

void AExtractionGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority())
	{
		// TODO: This fails to get on a dedicated server before clients connect and request points
		AActor* Points = UGameplayStatics::GetActorOfClass(GetWorld(), AActiveExtractionPoints::StaticClass());
		if (!IsValid(Points)) return;
		
		UE_LOG(LogTemp, Warning, TEXT("Valid Points"));
		ExtractionPoints = Cast<AActiveExtractionPoints>(Points);
	}
}

void AExtractionGameMode::AuthGetExtractionPoints(const APawn* PlayerPawn) const
{
	if (!HasAuthority()) return;
	if (!IsValid(ExtractionPoints)) return;
	if (!IsValid(PlayerPawn)) return;

	const FVector PlayerLocation = PlayerPawn->GetActorLocation();
	TArray<AExtractionPoint*> PlayerPoints = ExtractionPoints->GetPointsByDistance(PlayerLocation);
	// TODO: Debug to test remove when done
	for (const auto& PlayerPoint : PlayerPoints)
	{
		DrawDebugLine(GetWorld(), PlayerLocation, PlayerPoint->GetActorLocation(), FColor::Red, false, 10.f);
	}
}