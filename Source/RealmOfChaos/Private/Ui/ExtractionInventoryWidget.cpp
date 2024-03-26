// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/ExtractionInventoryWidget.h"	

#include "Components/InventoryComponent.h"
#include "Components/OverlaySlot.h"
#include "Widgets/InventoryGridWidget.h"


void UExtractionInventoryWidget::SetupInventoryGridWidget(UInventoryComponent* NewInventoryComponent)
{
	if (!IsValid(InventoryGridWidget)) return;

	InventoryComponent = NewInventoryComponent;
	SetGridTileSize();
}

void UExtractionInventoryWidget::SetGridTileSize()
{
	if (!IsValid(InventoryComponent)) return;
	
	if (UOverlaySlot* OverlaySlot = Cast<UOverlaySlot>(InventoryGridWidget->Slot))
	{
		const FVector2d GridSize = InventoryGridWidget->GetCachedGeometry().GetLocalSize();
		UE_LOG(LogTemp, Warning, TEXT("OverlaySlot %s"), *GridSize.ToString());

		// const float TileSize = GridSize.X / InventoryComponent->GetColumns();
		const float TileSize = GridSize.Y / InventoryComponent->GetRows();
		InventoryGridWidget->InitializeGrid(InventoryComponent, TileSize);
	}
}
