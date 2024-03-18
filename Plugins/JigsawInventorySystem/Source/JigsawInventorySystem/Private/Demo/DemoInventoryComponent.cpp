// Fill out your copyright notice in the Description page of Project Settings.


#include "Demo/DemoInventoryComponent.h"
#include "Demo/InventoryDemoItem.h"


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
	Inventory = MakeUnique<TInventoryGrid<FInventoryDemoItem>>(SlotColumns, SlotRows);
	UE_LOG(LogTemp, Warning, TEXT("Inventory created with %d rows and %d columns"), SlotRows, SlotColumns);
	
	const FInventoryDemoItem DemoItemOne = FInventoryDemoItem(FName("Item1"), FString("This is item 1"), 100);
	Inventory->AddItem(DemoItemOne, 0, 0, 2, 2);
	
	// Try to add item to the occupied slot
	const FInventoryDemoItem DemoItemTwo = FInventoryDemoItem(FName("Item2"), FString("This is item 2"), 200);
	Inventory->AddItem(DemoItemTwo, 0, 0, 1, 1);
	Inventory->AddItem(DemoItemTwo, 1, 0, 1, 1);
	Inventory->AddItem(DemoItemTwo, 0, 1, 1, 1);
	Inventory->AddItem(DemoItemTwo, 1, 1, 1, 1);
	
	// Try to add item outside the grid
	Inventory->AddItem(DemoItemOne, 10, 5, 2, 2);
	
	// Try to add item in the grid but reaches outside the grid
	Inventory->AddItem(DemoItemOne, 2, 1, 2, 2);

	// // Successfully add item
	Inventory->AddItem(DemoItemOne, 0, 2, 2, 2);
}