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

void UGroundItemsWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
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
			ItemWidget->InitializeItem(Item->GetItemObject(), TileSize);
			ItemScrollBox->AddChild(ItemWidget);
			if (UScrollBoxSlot* ScrollSlot = Cast<UScrollBoxSlot>(ItemWidget->Slot))
			{
				ScrollSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Left);
				ScrollSlot->SetPadding(FMargin(ItemSlotMargin));
			}
		}
	}
}
