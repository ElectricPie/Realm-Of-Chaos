// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GroundItemsWidget.generated.h"

class UVerticalBox;
class UItemWidget;
class APlayerCharacter;
/**
 * 
 */
UCLASS()
class REALMOFCHAOS_API UGroundItemsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void Initialize(APlayerCharacter* NewPlayerCharacter, float NewTileSize);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Widgets", meta=(AllowPrivateAccess="true"))
	TSubclassOf<UItemWidget> ItemWidgetClass;
	UPROPERTY(BlueprintReadOnly, Category="Widgets", meta=(AllowPrivateAccess="true", BindWidget))
	UVerticalBox* ItemListBox;
	
	float TileSize = 50.f;
	
	UFUNCTION()
	void OnItemNearby(TArray<AItemActor*> NearbyItems);
};
