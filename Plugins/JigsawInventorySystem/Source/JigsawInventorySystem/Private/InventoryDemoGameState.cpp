// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryDemoGameState.h"

#include "Items/ItemActor.h"
#include "Items/ItemObject.h"
#include "Kismet/GameplayStatics.h"

void AInventoryDemoGameState::PlaceItemInWorld(UItemObject* ItemObject)
{
	if (!IsValid(ItemObject)) return;
	
	AItemActor* NewItemActor = GetWorld()->SpawnActor<AItemActor>(ItemObject->GetItemClass(), FVector::ZeroVector, FRotator::ZeroRotator);
	for (const auto& Location : ItemLocations)
	{
		if (!GetWorld()->EncroachingBlockingGeometry(NewItemActor, Location, FRotator::ZeroRotator))
		{
			NewItemActor->SetActorLocation(Location);
			return;
		}
	}
}

void AInventoryDemoGameState::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> Items;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AItemActor::StaticClass(), Items);
	for (const auto& Item : Items)
	{
		ItemLocations.Add(Item->GetActorLocation());
	}
}
