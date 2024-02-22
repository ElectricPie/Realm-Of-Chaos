#include "InventoryGrid.h"

template <typename T>
TInventoryGrid<T>::TInventoryGrid(const int32 Rows, const int32 Columns): Rows(Rows), Columns(Columns)
{
	// Setup the grid
	for (int32 i = 0; i < Rows; i++)
	{
		Slots.Add(TArray<TUniquePtr<TInventoryItem<T>>>());
		for (int32 j = 0; j < Columns; j++)
		{
			Slots[i].Add(TUniquePtr<TInventoryItem<T>>());
		}
	}
}

template <typename T>
bool TInventoryGrid<T>::AddItem(const T& ItemToAdd, const int32 XPos, const int32 YPos, const int32 XSize,
	const int32 YSize)
{
	// TODO: Return enum instead of bool to indicate the reason why the item cannot be added
	// Check if items is inside the grid
	if (XPos > Columns || YPos > Rows)
	{
		UE_LOG(LogTemp, Warning, TEXT("Item outside of grid"));
		return false;
	}
	if (XPos + XSize > Columns || YPos + YSize > Rows)
	{
		UE_LOG(LogTemp, Warning, TEXT("Item reached outside of grid"));
		return false;
	}

	// Check if the slot and the surrounding slots are empty
	for (int32 i = YPos; i < YPos + YSize; i++)
	{
		for (int32 j = XPos; j < XPos + XSize; j++)
		{
			if (Slots[i][j].IsValid())
			{
				UE_LOG(LogTemp, Warning, TEXT("Item in slot %d, %d preventing item being added"), XPos, YPos);
				return false;
			}
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Item added to grid at position %d, %d"), XPos, YPos);
	// Add the item to the grid
	for (int32 i = YPos; i < YPos + YSize; i++)
	{
		for (int32 j = XPos; j < XPos + XSize; j++)
		{
			Slots[i][j] = MakeUnique<TInventoryItem<T>>(ItemToAdd, XSize, YSize);
		}
	}

	return true;
}