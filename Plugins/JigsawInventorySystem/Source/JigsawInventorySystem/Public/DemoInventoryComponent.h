// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DemoInventoryComponent.generated.h"

class FInventoryGrid;

UCLASS(Blueprintable, ClassGroup=(JigsawInventory), meta=(BlueprintSpawnableComponent))
class JIGSAWINVENTORYSYSTEM_API UDemoInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDemoInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	TUniquePtr<FInventoryGrid> Inventory;
};
