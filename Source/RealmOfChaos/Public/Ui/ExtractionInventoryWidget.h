// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExtractionInventoryWidget.generated.h"

class UCanvasPanel;

/**
 * 
 */
UCLASS(HideDropdown)
class REALMOFCHAOS_API UExtractionInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintReadOnly, Category="Inventory", meta=(AllowPrivateAccess="true", BindWidget))
	UCanvasPanel* InventoryCanvas;
};
