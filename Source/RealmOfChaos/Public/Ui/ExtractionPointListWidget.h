// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExtractionPointListWidget.generated.h"

class UExtractionPointWidget;

/**
 * 
 */
UCLASS()
class REALMOFCHAOS_API UExtractionPointListWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Extraction", meta=(AllowPrivateAccess="true"))
	TSubclassOf<UExtractionPointWidget> ExtractionPointWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Extraction", meta=(AllowPrivateAccess="true", bindWidget))
	UExtractionPointWidget* TestExtractionPointWidget;	
};
