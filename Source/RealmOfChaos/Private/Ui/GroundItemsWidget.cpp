// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/GroundItemsWidget.h"

#include "Components/VerticalBox.h"
#include "Items/ItemActor.h"
#include "Player/PlayerCharacter.h"
#include "Widgets/ItemWidget.h"

void UGroundItemsWidget::Initialize(APlayerCharacter* PlayerCharacter, float NewTileSize)
{
	TileSize = NewTileSize;
	PlayerCharacter->OnItemNearbyEvent.AddDynamic(this, &UGroundItemsWidget::OnItemNearby);
}

void UGroundItemsWidget::OnItemNearby(TArray<AItemActor*> NearbyItems)
{
	if (!IsValid(ItemListBox) || !IsValid(ItemWidgetClass)) return;
	ItemListBox->ClearChildren();

	for (const auto& Item : NearbyItems)
	{
		if (IsValid(Item))
		{
			UItemWidget* ItemWidget = CreateWidget<UItemWidget>(GetWorld(), ItemWidgetClass);
			ItemWidget->InitializeItem(Item->GetItemObject(), TileSize);
			ItemListBox->AddChild(ItemWidget);
		}
	}
}
