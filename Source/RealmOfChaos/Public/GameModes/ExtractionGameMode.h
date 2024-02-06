// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "ExtractionGameMode.generated.h"

class AActiveExtractionPoints;
/**
 * 
 */
UCLASS()
class REALMOFCHAOS_API AExtractionGameMode : public AGameMode
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
	virtual void PostLogin(APlayerController* NewPlayer) override;

private:
	UPROPERTY()
	AActiveExtractionPoints* ExtractionPoints;
};
