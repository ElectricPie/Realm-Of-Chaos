// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExtractionPointListWidget.generated.h"

class UExtractionPointWidget;
class UVerticalBox;

/**
 * 
 */
UCLASS()
class REALMOFCHAOS_API UExtractionPointListWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void AddExtractionPoint(const FText& Name, const int32 Distance);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Extraction", meta=(AllowPrivateAccess="true"))
	TSubclassOf<UExtractionPointWidget> ExtractionPointWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Extraction", meta=(AllowPrivateAccess="true", BindWidget))
	UVerticalBox* ExtractionPointList;
	
	TArray<UExtractionPointWidget*> ExtractionPointWidgets;
};
