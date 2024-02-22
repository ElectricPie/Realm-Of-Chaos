#pragma once
#include "InventoryDemoItem.h"

template <class T>
struct TInventoryItem
{
	TInventoryItem(const T& Item, const int32 XSize, const int32 YSize): Item(MakeShared<T>(Item)),ItemXSize(XSize), ItemYSize(YSize)
	{
	}

	TSharedRef<T> GetItem() { return Item; }
	int32 GetItemXSize() const { return ItemXSize; }
	int32 GetItemYSize() const { return ItemYSize; }
	
private:
	TSharedRef<T> Item;
	int32 ItemXSize;
	int32 ItemYSize;
};


template <typename T>
class TInventoryGrid
{
public:
	TInventoryGrid(const int32 Rows, const int32 Columns);

	int32 GetRows() const { return Rows; }
	int32 GetColumns() const { return Columns; }

private:
	int32 Rows;
	int32 Columns;

	TArray<TArray<TUniquePtr<TInventoryItem<T>>>> Slots;
};
