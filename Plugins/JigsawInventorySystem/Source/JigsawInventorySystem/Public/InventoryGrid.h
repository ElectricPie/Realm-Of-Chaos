#pragma once

template <class T>
struct TInventoryItem
{
	TInventoryItem(const T& Item, const int32 XSize, const int32 YSize): Item(MakeShared<T>(Item)),ItemXSize(XSize), ItemYSize(YSize) {	}

	TSharedRef<T> GetItem() { return Item; }
	int32 GetItemXSize() const { return ItemXSize; }
	int32 GetItemYSize() const { return ItemYSize; }
	
private:
	TSharedRef<T> Item;
	int32 ItemXSize;
	int32 ItemYSize;
};

enum EInventoryAddError
{
	Success,
	OutOfBounds,
	ItemTooLarge,
	Occupied
};


template <typename T>
class TInventoryGrid
{
public:
	TInventoryGrid(const int32 GridRows, const int32 GridColumns): Rows(GridRows), Columns(GridColumns)
	{
		Slots.SetNum(GridRows);
		for (int32 i = 0; i < GridRows; i++)
		{
			Slots[i].SetNum(GridColumns);
		}
 	}

	int32 GetRows() const { return Rows; }
	int32 GetColumns() const { return Columns; }
	EInventoryAddError AddItem(const T& ItemToAdd, const int32 XPos, const int32 YPos, const int32 XSize, const int32 YSize);

	
private:
	int32 Rows;
	int32 Columns;
	
	TArray<TArray<TUniquePtr<TInventoryItem<T>>>> Slots;
};


template <typename T>
EInventoryAddError TInventoryGrid<T>::AddItem(const T& ItemToAdd, const int32 XPos, const int32 YPos, const int32 XSize,
	const int32 YSize)
{
	// Check if items is inside the grid
	if (XPos > Columns || YPos > Rows)
	{
		UE_LOG(LogTemp, Warning, TEXT("Item outside of grid"));
		return OutOfBounds;
	}
	if (XPos + XSize > Columns || YPos + YSize > Rows)
	{
		UE_LOG(LogTemp, Warning, TEXT("Item reached outside of grid"));
		return ItemTooLarge;
	}
	
	// Check if the slot and the surrounding slots are empty
	for (int32 i = YPos; i < YPos + YSize; i++)
	{
		for (int32 j = XPos; j < XPos + XSize; j++)
		{
			if (Slots[i][j].IsValid())
			{
				UE_LOG(LogTemp, Warning, TEXT("Item in slot %d, %d preventing item being added"), XPos, YPos);
				return Occupied;
			}
		}
	}
	
	// Add the item to the grid
	for (int32 i = YPos; i < YPos + YSize; i++)
	{
		for (int32 j = XPos; j < XPos + XSize; j++)
		{
			Slots[i][j] = MakeUnique<TInventoryItem<T>>(ItemToAdd, XSize, YSize);
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Item added to grid at position %d, %d"), XPos, YPos);

	return Success;
}
