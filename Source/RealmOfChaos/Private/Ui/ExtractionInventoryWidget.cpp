// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/ExtractionInventoryWidget.h"

#include "Components/InventoryComponent.h"
#include "Components/OverlaySlot.h"
#include "Widgets/InventoryGridWidget.h"
#include "Player/PlayerCharacter.h"
#include "Ui/GroundItemsWidget.h"


void UExtractionInventoryWidget::InitializeInventoryWidget(APlayerCharacter* PlayerCharacter)
{
	if (UInventoryComponent* PlayerInventoryComponent = PlayerCharacter->GetInventoryComponent())
	{
		InventoryComponent = PlayerInventoryComponent;
		SetGridTileSize();
	}

	GroundItemsWidget->Initialize(PlayerCharacter, TileSize);
}

void UExtractionInventoryWidget::SetGridTileSize()
{
	if (!IsValid(InventoryComponent) || !IsValid(InventoryGridWidget)) return;

	const FVector2d GridSize = InventoryGridWidget->GetCachedGeometry().GetLocalSize();
	// float TileSize = GridSize.X / InventoryComponent->GetColumns();
	TileSize = GridSize.Y / InventoryComponent->GetRows();
	InventoryGridWidget->InitializeGrid(InventoryComponent, TileSize);
}
