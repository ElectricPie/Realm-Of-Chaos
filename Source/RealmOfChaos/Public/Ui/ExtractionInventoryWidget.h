// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExtractionInventoryWidget.generated.h"

class UGroundItemsWidget;
class UOverlay;
class USizeBox;
class UCanvasPanel;
class APlayerCharacter;
class UInventoryComponent;
class UInventoryGridWidget;

/**
 * 
 */
UCLASS(HideDropdown)
class REALMOFCHAOS_API UExtractionInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	 * @brief This sets up the grid to fit inside its overlay slot so needs to be called a short time after beguin play
	 * @param PlayerCharacter The inventory component to use for the grid
	 */
	void InitializeInventoryWidget(APlayerCharacter* PlayerCharacter);

private:
	UPROPERTY(BlueprintReadOnly, Category="Widgets", meta=(AllowPrivateAccess="true", BindWidget))
	UCanvasPanel* InventoryCanvas;
	UPROPERTY(BlueprintReadOnly, Category="Widgets", meta=(AllowPrivateAccess="true", BindWidget))
	UOverlay* InventoryGridOverlay;
	UPROPERTY(BlueprintReadOnly, Category="Widgets", meta=(AllowPrivateAccess="true", BindWidget))
	UInventoryGridWidget* InventoryGridWidget;
	UPROPERTY(BlueprintReadOnly, Category="Widgets", meta=(AllowPrivateAccess="true", BindWidget))
	UGroundItemsWidget* GroundItemsWidget;
	UPROPERTY()
	UInventoryComponent* InventoryComponent;
	UPROPERTY(BlueprintReadOnly, Category="Inventory", meta=(AllowPrivateAccess="true"))
	float TileSize = 50.f;
	
	void SetGridTileSize();
};
