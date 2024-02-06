// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/ExtractionGameMode.h"

#include "Extraction/ActiveExtractionPoints.h"
#include "Extraction/ExtractionPoint.h"
#include "Kismet/GameplayStatics.h"
#include "States/ExtractionGameState.h"
#include "States/ExtractionPlayerState.h"

void AExtractionGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		AActor* Points = UGameplayStatics::GetActorOfClass(GetWorld(), AActiveExtractionPoints::StaticClass());
		if (!IsValid(Points)) return;
		ExtractionPoints = Cast<AActiveExtractionPoints>(Points);
	}
}

void AExtractionGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	// This doesn't work for listen server
	const AExtractionPlayerState* ExtractionPlayerState = NewPlayer->GetPlayerState<AExtractionPlayerState>();
	if (!IsValid(ExtractionPlayerState)) return;
	
	const APawn* PlayerPawn = NewPlayer->GetPawn();
	if (!IsValid(PlayerPawn)) return;

	const FVector PlayerLocation = PlayerPawn->GetActorLocation();
	// TODO: Debug to test remove
	TArray<AExtractionPoint*> PlayerPoints = ExtractionPoints->GetPointsByDistance(PlayerLocation); 
	for (const auto& PlayerPoint : PlayerPoints)
	{
		DrawDebugLine(GetWorld(), PlayerLocation, PlayerPoint->GetActorLocation(), FColor::Red, false, 10.f);
	}
}
