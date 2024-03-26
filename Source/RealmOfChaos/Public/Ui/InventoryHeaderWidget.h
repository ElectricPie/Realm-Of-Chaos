// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryHeaderWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class REALMOFCHAOS_API UInventoryHeaderWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativePreConstruct() override;
	
private:
	UPROPERTY(EditAnywhere, Category="Header Text", meta=(AllowPrivateAccess="true"))
	FText HeaderText = FText::FromString("Header");
	
	UPROPERTY(BlueprintReadOnly, Category="Header Text", meta=(AllowPrivateAccess="true", BindWidget))
	UTextBlock* HeaderTextWidget;
};
