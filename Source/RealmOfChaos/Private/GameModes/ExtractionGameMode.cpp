// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/ExtractionGameMode.h"

#include "EngineUtils.h"
#include "Engine/PlayerStartPIE.h"
#include "Extraction/ActiveExtractionPoints.h"
#include "Extraction/ExtractionPoint.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "States/ExtractionGameState.h"

void AExtractionGameMode::AuthGetExtractionPoints(const APawn& PlayerPawn)
{
	UE_LOG(LogTemp,	Warning, TEXT("Beep Boop"));
	
	if (!GetActiveExtractionPoints()) return;
	
	const FVector PlayerLocation = PlayerPawn.GetActorLocation();
	TArray<AExtractionPoint*> PlayerPoints = ActiveExtractionPoints->GetPointsByDistance(PlayerLocation);
	// TODO: Debug to test remove when done
	for (const auto& PlayerPoint : PlayerPoints)
	{
		DrawDebugLine(GetWorld(), PlayerLocation, PlayerPoint->GetActorLocation(), FColor::Red, false, 10.f);
	}
}

void AExtractionGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	GetActiveExtractionPoints();
}

void AExtractionGameMode::HandleMatchIsWaitingToStart()
{
	Super::HandleMatchIsWaitingToStart();
	
	GetActiveExtractionPoints();
}

AActor* AExtractionGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	if (!GetActiveExtractionPoints())
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to get Active Extraction Points for player spawning"));
		return nullptr;
	}
	UE_LOG(LogTemp, Warning, TEXT("Spawning Players"));

	// Choose a player start
	APlayerStart* FoundPlayerStart = nullptr;
	UClass* PawnClass = GetDefaultPawnClassForController(Player);
	APawn* PawnToFit = PawnClass ? PawnClass->GetDefaultObject<APawn>() : nullptr;
	TArray<APlayerStart*> UnOccupiedStartPoints;
	TArray<APlayerStart*> OccupiedStartPoints;
	UWorld* World = GetWorld();
	
	for (TActorIterator<APlayerStart> It(World); It; ++It)
	{
		APlayerStart* PlayerStart = *It;

		if (PlayerStart->IsA<APlayerStartPIE>())
		{
			// Always prefer the first "Play from Here" PlayerStart, if we find one while in PIE mode
			FoundPlayerStart = PlayerStart;
			break;
		}
		else
		{
			FVector ActorLocation = PlayerStart->GetActorLocation();
			const FRotator ActorRotation = PlayerStart->GetActorRotation();
			if (!World->EncroachingBlockingGeometry(PawnToFit, ActorLocation, ActorRotation))
			{
				UnOccupiedStartPoints.Add(PlayerStart);
			}
			else if (World->FindTeleportSpot(PawnToFit, ActorLocation, ActorRotation))
			{
				OccupiedStartPoints.Add(PlayerStart);
			}
		}
	}
	if (FoundPlayerStart == nullptr)
	{
		if (UnOccupiedStartPoints.Num() > 0)
		{
			FoundPlayerStart = UnOccupiedStartPoints[FMath::RandRange(0, UnOccupiedStartPoints.Num() - 1)];
		}
		else if (OccupiedStartPoints.Num() > 0)
		{
			FoundPlayerStart = OccupiedStartPoints[FMath::RandRange(0, OccupiedStartPoints.Num() - 1)];
		}
	}
	return FoundPlayerStart;
}

bool AExtractionGameMode::GetActiveExtractionPoints()
{
	if (!IsValid(ActiveExtractionPoints))
	{
		AActor* ExtractionPointsActor = UGameplayStatics::GetActorOfClass(GetWorld(), AActiveExtractionPoints::StaticClass());
		if (!IsValid(ExtractionPointsActor))
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to get Active Extraction Points"))
			return false;
		}
		ActiveExtractionPoints = Cast<AActiveExtractionPoints>(ExtractionPointsActor);
	}

	return true;
}
