// ifll out your copyright notice in the Description page of Project Settings.


#include "Ui/GroundItemsWidget.h"

#include "Player/PlayerCharacter.h"

void UGroundItemsWidget::Initialize(APlayerCharacter* PlayerCharacter, float NewTileSize)
{
	TileSize = NewTileSize;
	PlayerCharacter->OnItemNearbyEvent.AddDynamic(this, &UGroundItemsWidget::OnItemNearby);
}

void UGroundItemsWidget::OnItemNearby(TArray<AItemActor*> NearbyItems)
{
	UE_LOG(LogTemp, Warning, TEXT("Item nearby"));
}
