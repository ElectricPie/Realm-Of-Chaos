// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UItemObject;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryChangedSignature);

USTRUCT(BlueprintType)
struct FTile
{
	GENERATED_BODY()

	FTile(): X(0), Y(0)
	{
	}

	FTile(const int32 NewX, const int32 NewY): X(NewX), Y(NewY)
	{
	}

	FTile (const FIntPoint Point): X(Point.X), Y(Point.Y)
	{
	}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Cell");
	int32 X;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Cell");
	int32 Y;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JIGSAWINVENTORYSYSTEM_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();
	
	// TODO: Should probably be private with functions bind/unbind
	UPROPERTY(BlueprintAssignable, Category="Inventory")
	FOnInventoryChangedSignature OnInventoryChangedEvent;
	
	UFUNCTION(BlueprintCallable, Category="Inventory")
	int32 GetColumns() const { return Columns; }
	UFUNCTION(BlueprintCallable, Category="Inventory")
	int32 GetRows() const { return Rows; }

	/**
	 * @brief Gets a Tile corresponding to the given index to a tile in the inventory
	 */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	FTile IndexToTile(const int32 Index) const { return FTile(Index % Columns, Index / Columns); }
	/**
	 * @brief Gets the index of the given relative to the array inventory array, will clamp to the array bounds
	 */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	int32 TileToIndex(const FTile Tile) const { return FMath::Clamp(Tile.X + Tile.Y * Columns, 0, Items.Num() - 1); }
	/**
	 * @brief Tests if the Tile is valid inside of the inventory
	 * @param Tile The Tile to test
	 * @return true if the Tile is valid, otherwise false
	 */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool IsTileValid(const FTile Tile) const { return Tile.X >= 0 && Tile.X < Columns && Tile.Y >= 0 && Tile.Y < Rows; }
	/**
	 * @brief Check if the inventory has space for the item at the specified index
	 * @param ItemObject The item to check for space
	 * @param TopLeftIndex The index of the top left Tile to check for space from
	 * @return true if the inventory has space, otherwise false
	 */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool IsSpaceAvailable(const UItemObject* ItemObject, const int32 TopLeftIndex);
	/**
	 * @brief Attempts to add an item to the inventory in the first available spaces
	 * @param ItemObject The item to add
	 * @return true if the item was added, otherwise false
	 */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool TryAddItem(UItemObject* ItemObject);
	/**
	 * @brief Attempts to add an item to the inventory at the specified index
	 * @param ItemObject The item to add
	 * @param TopLeftIndex The index to add the item at
	 * @return true if the item was added, otherwise false
	 */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool TryAddItemAtIndex(UItemObject* ItemObject, const int32 TopLeftIndex);
	UFUNCTION(BlueprintCallable, Category="Inventory")
	TMap<UItemObject*, FTile> GetAllItems() const;
	
	/**
	 * @brief Removes the item from the inventory
	 * @param ItemObject The item to be removed
	 */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	void RemoveItem(UItemObject* ItemObject);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory", meta=(AllowPrivateAccess="true"))
	int32 Columns = 5;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory", meta=(AllowPrivateAccess="true"))
	int32 Rows = 10;

	UPROPERTY(BlueprintReadOnly, Category="Inventory", meta=(AllowPrivateAccess="true"))
	TArray<UItemObject*> Items;
	UPROPERTY(BlueprintReadOnly, Category="Inventory", meta=(AllowPrivateAccess="true"))
	bool bIsDirty = false;
	
	/**
	 * @brief Attempts to get an item at the specified index
	 * @param Index The index to peek
	 * @param OutItemObject 
	 * @return true if an item was found, otherwise false
	 */
	UFUNCTION(BlueprintCallable, Category="Inventory", meta=(HideSelfPin="true"))
	bool GetItemAtIndex(const int32 Index, UItemObject*& OutItemObject);
	UFUNCTION()
	void AddItemAtIndex(UItemObject* ItemObject, const int32 TopLeftIndex);
};
