// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DemoInventoryComponent.generated.h"

class FInventoryDemoItem;
template <typename T>
class TInventoryGrid;

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

private:
	TUniquePtr<TInventoryGrid<FInventoryDemoItem>> Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory", meta=(AllowPrivateAccess="true"))
	int32 SlotRows = 5;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory", meta=(AllowPrivateAccess="true"))
	int32 SlotColumns = 2;
};
