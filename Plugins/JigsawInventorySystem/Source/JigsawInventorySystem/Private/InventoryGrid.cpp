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
