// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "ExtractionGameMode.generated.h"

class AActiveExtractionPoints;
class ATopDownPlayerController;
/**
 * 
 */
UCLASS()
class REALMOFCHAOS_API AExtractionGameMode : public AGameMode
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
	virtual void HandleMatchIsWaitingToStart() override;
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

private:
	UPROPERTY(VisibleAnywhere)
	AActiveExtractionPoints* ActiveExtractionPoints;

	/**
	 * @brief Attempts to get the AActiveExtractionPoints in the world for the ActiveExtractionPoints variable
	 * @return true if successfully otherwise false
	 */
	bool GetActiveExtractionPoints();
};
