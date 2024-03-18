// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets//InventoryGridWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/SizeBox.h"

void UInventoryGridWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
}

void UInventoryGridWidget::InitializeGrid(const int32 Columns, const int32 Rows, const float NewTileSize)
{
	TileSize = NewTileSize;

	GridSizeBox->SetWidthOverride(TileSize * Columns);
	GridSizeBox->SetHeightOverride(TileSize * Rows);

	for (int32 i = 0; i < Columns; i++)
	{
		const FLine NewLine(FVector2D(i * TileSize, 0.f), FVector2D(i, Rows) * TileSize);
		GridLines.Add(NewLine);
	}

	for (int32 i = 0; i < Rows; i++)
	{
		const FLine NewLine(FVector2D(0.f, i * TileSize), FVector2D(Columns, i) * TileSize);
		GridLines.Add(NewLine);
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
