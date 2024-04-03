// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/GroundItemsWidget.h"

#include "Components/ScrollBox.h"
#include "Components/ScrollBoxSlot.h"
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
	if (!IsValid(ItemScrollBox) || !IsValid(ItemWidgetClass)) return;
	ItemScrollBox->ClearChildren();

	for (const auto& Item : NearbyItems)
	{
		if (IsValid(Item))
		{
			UItemWidget* ItemWidget = CreateWidget<UItemWidget>(GetWorld(), ItemWidgetClass);
			ItemWidget->OnRemovedEvent.AddDynamic(this, &UGroundItemsWidget::OnItemWidgetRemoved);
			ItemWidget->InitializeItem(Item->GetItemObject(), TileSize);
			ItemScrollBox->AddChild(ItemWidget);

			ItemWidgets.Add(Item->GetItemObject(), Item);
			
			if (UScrollBoxSlot* ScrollSlot = Cast<UScrollBoxSlot>(ItemWidget->Slot))
			{
				ScrollSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Left);
				ScrollSlot->SetPadding(FMargin(ItemSlotMargin));
			}
		}
	}
}

void UGroundItemsWidget::OnItemWidgetRemoved(UItemObject* ItemObject)
{
	if (AItemActor* ItemActor = ItemWidgets.FindAndRemoveChecked(ItemObject))
	{
		ItemActor->Destroy();
	}
}


