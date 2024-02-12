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


void AExtractionGameMode::StartPlayerExtraction(ATopDownPlayerController* PlayerController, const AExtractionPoint* ExtractionPoint)
{
	if (!IsValid(PlayerController) || !IsValid(ExtractionPoint)) return;

	// Check that the extraction point the player is at is one they have been assigned
	if (!PlayerController->GetExtractionPoints().Contains(ExtractionPoint))
	{
		UE_LOG(LogTemp, Error, TEXT("%s attempted to extract at non assigned Extraction Point"), *PlayerController->GetActorNameOrLabel());
		return;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Starting extraction for %s at %s"), *PlayerController->GetActorNameOrLabel(), *ExtractionPoint->GetPointName().ToString());
	
	// Start a timer to extract the player
	FTimerHandle PlayerTimerHandle;
	const FTimerDelegate ExtractionDelegate = FTimerDelegate::CreateUObject(this, &AExtractionGameMode::ExtractPlayer, PlayerController);
	GetWorldTimerManager().SetTimer(PlayerTimerHandle, ExtractionDelegate, ExtractionPoint->GetExtractionTime(), false);
	
	ExtractionCountdowns.Add(PlayerController, PlayerTimerHandle);
}

void AExtractionGameMode::CancelPlayerExtraction(ATopDownPlayerController* PlayerController)
{
	if (!IsValid(PlayerController) || !ExtractionCountdowns.Contains(PlayerController)) return;
	
	UE_LOG(LogTemp, Warning, TEXT("Stopping extraction for %s"), *PlayerController->GetActorNameOrLabel());
	
	FTimerHandle PlayerCountdown = ExtractionCountdowns.FindAndRemoveChecked(PlayerController);
	GetWorldTimerManager().ClearTimer(PlayerCountdown);
}

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
		const TArray<const AExtractionPoint*> SelectedExtractionPoints = ActiveExtractionPoints->GetPointsByDistance(FoundPlayerStart->GetActorLocation());
		TopDownPlayer->AuthSetExtractionPoints(SelectedExtractionPoints);
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

void AExtractionGameMode::ExtractPlayer(ATopDownPlayerController* PlayerController)
{
	if (!ExtractionCountdowns.Contains(PlayerController)) return;
	ExtractionCountdowns.Remove(PlayerController);
	
	UE_LOG(LogTemp, Warning, TEXT("Extracted %s"), *PlayerController->GetActorNameOrLabel());
	// TODO: Handle player extraction
	OnPlayerExtracted.Broadcast(PlayerController);
}
