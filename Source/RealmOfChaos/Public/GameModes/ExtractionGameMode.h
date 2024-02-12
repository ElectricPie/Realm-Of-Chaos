// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Player/TopDownPlayerController.h"
#include "ExtractionGameMode.generated.h"

class AActiveExtractionPoints;
class ATopDownPlayerController;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerExtractedDelegate, ATopDownPlayerController*, PlayerController);

/**
 * 
 */
UCLASS()
class REALMOFCHAOS_API AExtractionGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	/**
	 * @brief Starts a timer for the player, if player stays inside the Extraction Point they will be extracted
	 * @param PlayerController The player inside the extraction point
	 * @param ExtractionPoint The extraction point the player is at
	 */
	void StartPlayerExtraction(ATopDownPlayerController* PlayerController, const AExtractionPoint* ExtractionPoint);
	/**
	 * @brief Cancels a players extraction timer if there is one for the player
	 * @param PlayerController The player to cancel the timer for
	 */
	void CancelPlayerExtraction(ATopDownPlayerController* PlayerController);

protected:
	virtual void BeginPlay() override;
	
	virtual void HandleMatchIsWaitingToStart() override;
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

private:
	UPROPERTY(VisibleAnywhere)
	AActiveExtractionPoints* ActiveExtractionPoints;
	UPROPERTY()
	TMap<ATopDownPlayerController*, FTimerHandle> ExtractionCountdowns;
	UPROPERTY()
	FPlayerExtractedDelegate OnPlayerExtracted;

	/**
	 * @brief Attempts to get the AActiveExtractionPoints in the world for the ActiveExtractionPoints variable
	 * @return true if successfully otherwise false
	 */
	bool GetActiveExtractionPoints();

	void ExtractPlayer(ATopDownPlayerController* PlayerController);
};
