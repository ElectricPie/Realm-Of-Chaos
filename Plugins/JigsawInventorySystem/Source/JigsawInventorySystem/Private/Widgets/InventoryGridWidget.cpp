// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets//InventoryGridWidget.h"

#include "InventoryDemoGameState.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/SizeBox.h"
#include "Components/InventoryComponent.h"
#include "Items/ItemObject.h"
#include "Slate/SlateBrushAsset.h"
#include "Widgets/ItemWidget.h"

void UInventoryGridWidget::InitializeGrid(UInventoryComponent* NewInventoryComponent, const float NewTileSize)
{
	if (!IsValid(NewInventoryComponent)) return;

	InventoryComponent = NewInventoryComponent;
	TileSize = NewTileSize;

	const int32 Columns = InventoryComponent->GetColumns();
	const int32 Rows = InventoryComponent->GetRows();
	GridSizeBox->SetWidthOverride(TileSize * Columns);
	GridSizeBox->SetHeightOverride(TileSize * Rows);

	// Calculate grid lines to be drawn in the paint method`
	for (int32 i = 0; i < Columns + 1; i++)
	{
		const FLine NewLine(FVector2D(i * TileSize, 0.f), FVector2D(i, Rows) * TileSize);
		GridLines.Add(NewLine);
	}
	for (int32 i = 0; i < Rows + 1; i++)
	{
		const FLine NewLine(FVector2D(0.f, i * TileSize), FVector2D(Columns, i) * TileSize);
		GridLines.Add(NewLine);
	}
	InventoryComponent->OnInventoryChangedEvent.AddDynamic(this, &UInventoryGridWidget::Refresh);

	Refresh();
}

void UInventoryGridWidget::Refresh()
{
	if (!IsValid(GridCanvasPanel)) return;
	if (ItemWidgetClass == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ItemWidgetClass is not set in InventoryGridWidget"));
		return;
	}

	GridCanvasPanel->ClearChildren();
	TMap<UItemObject*, FTile> AllItems = InventoryComponent->GetAllItems();
	for (auto& [ItemObject, TopLeftTile] : AllItems)
	{
		UItemWidget* ItemWidget = CreateWidget<UItemWidget>(GetWorld(), ItemWidgetClass);
		ItemWidget->InitializeItem(ItemObject, TileSize);
		ItemWidget->OnRemovedEvent.AddDynamic(this, &UInventoryGridWidget::OnItemRemoved);

		UCanvasPanelSlot* NewItemCanvasSlot = GridCanvasPanel->AddChildToCanvas(ItemWidget);
		NewItemCanvasSlot->SetAutoSize(true);
		NewItemCanvasSlot->SetPosition(FVector2D(TopLeftTile.X, TopLeftTile.Y) * TileSize);
	}
}

void UInventoryGridWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!IsValid(DropLocationBrush))
	{
		UE_LOG(LogTemp, Error, TEXT("DropLocationBrush is not set in InventoryGridWidget"));
	}
}

int32 UInventoryGridWidget::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
                                        const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements,
                                        int32 LayerId,
                                        const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	FPaintContext Context(AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

	// Draw the grid lines
	for (auto& Line : GridLines)
	{
		UWidgetBlueprintLibrary::DrawLine(Context, Line.Start, Line.End, GridLineColor, true, 1.f);
	}

	// Draw the drop location box and colour
	if (UWidgetBlueprintLibrary::IsDragDropping() && bDrawDropLocation)
	{
		if (const UItemObject* ItemObject = Cast<UItemObject>(
			UWidgetBlueprintLibrary::GetDragDroppingContent()->Payload))
		{
			FLinearColor DropColor = CannotDropColor;
			if (InventoryComponent->IsSpaceAvailable(
				ItemObject, InventoryComponent->TileToIndex(DraggedItemTopLeftTile)))
			{
				DropColor = CanDropColor;
			}

			if (IsValid(DropLocationBrush))
			{
				const FVector2D Position = FVector2D(DraggedItemTopLeftTile.X, DraggedItemTopLeftTile.Y) * TileSize;
				const FVector2D Size = ItemObject->GetSize() * TileSize;
				UWidgetBlueprintLibrary::DrawBox(Context, Position, Size, DropLocationBrush, DropColor);
			}
		}
	}

	return Super::NativePaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle,
	                          bParentEnabled);
}

bool UInventoryGridWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                        UDragDropOperation* InOperation)
{
	if (UItemObject* ItemObject = Cast<UItemObject>(InOperation->Payload))
	{
		const int32 TopLeftIndex = InventoryComponent->TileToIndex(DraggedItemTopLeftTile);
		// Try to add it back to the new position
		if (!InventoryComponent->TryAddItemAtIndex(ItemObject, TopLeftIndex))
		{
			// Try place the item any where in the inventory
			if (!InventoryComponent->TryAddItem(ItemObject))
			{
				// Place the item in the world if it cannot be placed in the inventory
				if (AInventoryDemoGameState* GameState = GetWorld()->GetGameState<AInventoryDemoGameState>())
				{
					GameState->PlaceItemInWorld(ItemObject);
				}
			}
		}
	}

	return true;
}

bool UInventoryGridWidget::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                            UDragDropOperation* InOperation)
{
	const FVector2D MousePosition = InGeometry.AbsoluteToLocal(InDragDropEvent.GetScreenSpacePosition());
	const FMousePositionInTile PositionInTile = MousePositionInTile(MousePosition);

	if (const UItemObject* ItemObject = Cast<UItemObject>(InOperation->Payload))
	{
		FIntPoint ItemSize = ItemObject->GetSize();
		if (PositionInTile.bIsRight)
		{
			if (ItemSize.X > 0)
			{
				ItemSize.X--;
			}
		}
		if (PositionInTile.bIsDown)
		{
			if (ItemSize.Y > 0)
			{
				ItemSize.Y--;
			}
		}

		const FVector2D CellPosition = MousePosition / TileSize - ItemSize / 2;
		DraggedItemTopLeftTile = FIntPoint(FMath::FloorToInt(CellPosition.X), FMath::FloorToInt(CellPosition.Y));
	}

	return true;
}

void UInventoryGridWidget::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                             UDragDropOperation* InOperation)
{
	Super::NativeOnDragEnter(InGeometry, InDragDropEvent, InOperation);

	bDrawDropLocation = true;
}

void UInventoryGridWidget::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);

	bDrawDropLocation = false;
}

FReply UInventoryGridWidget::NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::R)
	{
		const UDragDropOperation* Operation = UWidgetBlueprintLibrary::GetDragDroppingContent();
		if (UItemObject* ItemObject = Cast<UItemObject>(Operation->Payload))
		{
			ItemObject->Rotate();
			if (UItemWidget* ItemWidget = Cast<UItemWidget>(Operation->DefaultDragVisual))
			{
				ItemWidget->Refresh();
			}
		}
	}

	return FReply::Handled();
}

void UInventoryGridWidget::OnItemRemoved(UItemObject* RemovedItem)
{
	if (!IsValid(InventoryComponent)) return;
	InventoryComponent->RemoveItem(RemovedItem);
}

FMousePositionInTile UInventoryGridWidget::MousePositionInTile(const FVector2D MousePosition) const
{
	FMousePositionInTile MousePositionInTile;
	if (fmod(MousePosition.X, TileSize) > TileSize / 2)
	{
		MousePositionInTile.bIsRight = true;
	}
	if (fmod(MousePosition.Y, TileSize) > TileSize / 2)
	{
		MousePositionInTile.bIsDown = true;
	}

	return MousePositionInTile;
}
