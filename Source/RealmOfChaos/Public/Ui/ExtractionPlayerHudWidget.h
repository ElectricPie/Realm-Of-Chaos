// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExtractionPlayerHudWidget.generated.h"

class UExtractionPointListWidget;

/**
 * 
 */
UCLASS(HideDropdown)
class REALMOFCHAOS_API UExtractionPlayerHudWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UExtractionPointListWidget* GetExtractionPointListWidget() const { return ExtractionPointListWidget; }
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Extraction", meta=(AllowPrivateAccess="true", BindWidget))
	UExtractionPointListWidget* ExtractionPointListWidget;
};
