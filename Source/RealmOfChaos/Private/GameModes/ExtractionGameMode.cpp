// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/ExtractionGameMode.h"

#include "EngineUtils.h"
#include "Engine/PlayerStartPIE.h"
#include "Extraction/ActiveExtractionPoints.h"
#include "Extraction/ExtractionPoint.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "Player/TopDownPlayerController.h"
#include "States/ExtractionGameState.h"


void AExtractionGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AExtractionGameMode::HandleMatchIsWaitingToStart()
{
	Super::HandleMatchIsWaitingToStart();
}

AActor* AExtractionGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	if (!GetActiveExtractionPoints())
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get Active Extraction Points for player spawning"));
		return nullptr;
	}
	ATopDownPlayerController* TopDownPlayer = Cast<ATopDownPlayerController>(Player);
	if (!IsValid(TopDownPlayer))
	{
		UE_LOG(LogTemp, Error, TEXT("Extraction Gamemode must use TopDownPlayerController"));
		return nullptr;
	}
	UE_LOG(LogTemp, Warning, TEXT("Spawning Player"));

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

	// Get the extraction points for the player
	if (FoundPlayerStart != nullptr)
	{
		TArray<const AExtractionPoint*> SelectedExtractionPoints = ActiveExtractionPoints->GetPointsByDistance(FoundPlayerStart->GetActorLocation());
		// TODO: Debug remove when done
		if (World->GetNetMode() != NM_DedicatedServer)
		{
			for (auto& Point : SelectedExtractionPoints)
			{
				DrawDebugLine(World, FoundPlayerStart->GetActorLocation(), Point->GetActorLocation(), FColor::Green, false, 10.f);
			}
		}
		TopDownPlayer->SetExtractionPoints(SelectedExtractionPoints);
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
