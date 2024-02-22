// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoInventoryComponent.h"

#include "InventoryGrid.h"

// Sets default values for this component's properties
UDemoInventoryComponent::UDemoInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UDemoInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Inventory = MakeUnique<TInventoryGrid<FInventoryDemoItem>>(SlotRows, SlotColumns);
	UE_LOG(LogTemp, Warning, TEXT("Inventory created with %d rows and %d columns"), SlotRows, SlotColumns);
}