// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets//InventoryGridWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/SizeBox.h"
#include "Components/InventoryComponent.h"
#include "Widgets/ItemWidget.h"

void UInventoryGridWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
}

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

int32 UInventoryGridWidget::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
                                        const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
                                        const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	FPaintContext Context(AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
	for (auto& Line : GridLines)
	{
		UWidgetBlueprintLibrary::DrawLine(Context, Line.Start, Line.End, GridLineColor, true, 1.f);
	}
	
	return Super::NativePaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle,
	                          bParentEnabled);
}

void UInventoryGridWidget::OnItemRemoved(UItemObject* RemovedItem)
{
	if (!IsValid(InventoryComponent)) return;
	InventoryComponent->RemoveItem(RemovedItem);
}
