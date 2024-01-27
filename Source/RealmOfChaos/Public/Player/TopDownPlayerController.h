// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TopDownPlayerController.generated.h"

class APlayerCharacter;

/**
 * 
 */
UCLASS()
class REALMOFCHAOS_API ATopDownPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, Category="Input")
	float RaycastLimit = 3000.f;

	UPROPERTY()
	APlayerCharacter* PlayerCharacter;
};
