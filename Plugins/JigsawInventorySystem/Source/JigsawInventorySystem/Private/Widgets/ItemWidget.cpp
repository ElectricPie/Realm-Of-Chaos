// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ItemWidget.h"

#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Items/ItemObject.h"

void UItemWidget::InitializeItem(UItemObject* NewItem, float NewTileSize)
{
	ItemObject = NewItem;
	TileSize = NewTileSize;
	
	Refresh();
}

void UItemWidget::Refresh()
{
	if (!IsValid(ItemObject)) return;
	if (!IsValid(BackgroundSizeBox)) return;
	
	const FVector2D WidgetSize = FVector2D(ItemObject->GetSize()) * TileSize;
	BackgroundSizeBox->SetWidthOverride(WidgetSize.X);
	BackgroundSizeBox->SetHeightOverride(WidgetSize.Y);
	
	ItemIcon->SetBrushFromMaterial(ItemObject->GetIcon());
}

void UItemWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	BackgroundBorder->SetBrushColor(HoveredBackgroundColor);
}

void UItemWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	BackgroundBorder->SetBrushColor(BackgroundColor);
}
