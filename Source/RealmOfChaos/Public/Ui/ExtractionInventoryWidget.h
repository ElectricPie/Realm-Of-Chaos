// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExtractionInventoryWidget.generated.h"

class UOverlay;
class USizeBox;
class UCanvasPanel;
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
	 * @param NewInventoryComponent The inventory component to use for the grid
	 */
	void SetupInventoryGridWidget(UInventoryComponent* NewInventoryComponent);

private:
	UPROPERTY(BlueprintReadOnly, Category="Inventory", meta=(AllowPrivateAccess="true", BindWidget))
	UCanvasPanel* InventoryCanvas;
	UPROPERTY(BlueprintReadOnly, Category="Inventory", meta=(AllowPrivateAccess="true", BindWidget))
	UOverlay* InventoryGridOverlay;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Inventory", meta=(AllowPrivateAccess="true", BindWidget))
	UInventoryGridWidget* InventoryGridWidget;
	UPROPERTY()
	UInventoryComponent* InventoryComponent;

	void SetGridTileSize();
};
