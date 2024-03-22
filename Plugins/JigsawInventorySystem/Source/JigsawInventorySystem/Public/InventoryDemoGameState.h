// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "InventoryDemoGameState.generated.h"

class UItemObject;
/**
 * 
 */
UCLASS()
class JIGSAWINVENTORYSYSTEM_API AInventoryDemoGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Inventory")
	void PlaceItemInWorld(UItemObject* ItemObject);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TArray<FVector> ItemLocations;
	UPROPERTY()
	int32 CurrentPositionIndex = 0;
};
