// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemWidget.generated.h"

class UOverlay;
class USizeBox;
class UImage;

/**
 * 
 */
UCLASS()
class JIGSAWINVENTORYSYSTEM_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	// May need to change Overlay to CanvasPanel
	UPROPERTY(BlueprintReadOnly, Category="Item", meta=(AllowPrivateAccess="true", BindWidget))
	UOverlay* ItemOverlay;
	UPROPERTY(BlueprintReadOnly, Category="Item", meta=(AllowPrivateAccess="true", BindWidget))
	USizeBox* BackgroundSizeBox;
	UPROPERTY(BlueprintReadOnly, Category="Item", meta=(AllowPrivateAccess="true", BindWidget))
	UImage* ItemIcon;
};
