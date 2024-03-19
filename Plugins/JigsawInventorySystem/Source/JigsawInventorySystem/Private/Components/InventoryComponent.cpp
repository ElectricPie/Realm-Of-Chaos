// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"

#include "Items/ItemObject.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

bool UInventoryComponent::IsSpaceAvailable(const UItemObject* ItemObject, const int32 TopLeftIndex)
{
	const FTile Tile = IndexToTile(TopLeftIndex);
	const FIntPoint ItemSize = ItemObject->GetSize();

	for (int32 x = Tile.X; x < Tile.X + ItemSize.X; x++)
	{
		for (int32 y = Tile.Y; y < Tile.Y + ItemSize.Y; y++)
		{
			const FTile CurrentTile = FTile(x, y);
			if (!IsTileValid(CurrentTile)) return false;
			
			UItemObject* Item;
			if (!GetItemAtIndex(TileToIndex(CurrentTile), Item)) return false;
			if (IsValid(Item)) return false;
		}
	}
	
	return true;
}

bool UInventoryComponent::TryAddItem(UItemObject* ItemObject)
{
	if (!IsValid(ItemObject)) return false;
	
	for (int32 i = 0; i < Items.Num(); i++)
	{
		if (IsSpaceAvailable(ItemObject, i))
		{
			AddItemAtIndex(ItemObject, i);
			return true;
		}
	}
	
	return false;
}

TMap<UItemObject*, FTile> UInventoryComponent::GetAllItems() const
{
	TMap<UItemObject*, FTile> AllItems;
	for (int32 i = 0; i < Items.Num(); i++)
	{
		if (!IsValid(Items[i])) continue;
		if (AllItems.Contains(Items[i])) continue;

		AllItems.Add(Items[i], IndexToTile(i));
	}

	return AllItems;
}

void UInventoryComponent::RemoveItem(UItemObject* ItemObject)
{
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Items.SetNum(Columns * Rows);
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (bIsDirty)
	{
		bIsDirty = false;
		OnInventoryChangedEvent.Broadcast();
	}
}

bool UInventoryComponent::GetItemAtIndex(const int32 Index, UItemObject*& OutItemObject)
{
	if (!Items.IsValidIndex(Index)) return false;

	OutItemObject = Items[Index];
	return true;
}

void UInventoryComponent::AddItemAtIndex(UItemObject* ItemObject, const int32 TopLeftIndex)
{
	const FTile Cell = IndexToTile(TopLeftIndex);
	const FIntPoint ItemSize = ItemObject->GetSize();

	for (int32 x = Cell.X; x < Cell.X + ItemSize.X; x++)
	{
		for (int32 y = Cell.Y; y < Cell.Y + ItemSize.Y; y++)
		{
			Items[TileToIndex(FTile(x, y))] = ItemObject;
		}
	}

	bIsDirty = true;
}