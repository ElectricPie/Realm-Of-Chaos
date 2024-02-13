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
	/**
	 * @brief Adds an extraction point to the list
	 * @param Name The name of the extraction point
	 * @param Distance The distance to the extraction point in meters
	 */
	void AddExtractionPoint(const FText& Name, const int32 Distance);
	/**
	 * @brief Removes an extraction point from the list
	 * @param Index The index of the extraction point to remove
	 */
	void RemoveExtractionPoint(const int32 Index);
	/**
	 * @brief Updates the distance to an extraction point
	 * @param Index The index of the extraction point to update
	 * @param Distance The new distance to the extraction point in meters
	 */
	void UpdateExtractionPoint(const int32 Index, const int32 Distance);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Extraction", meta=(AllowPrivateAccess="true"))
	TSubclassOf<UExtractionPointWidget> ExtractionPointWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Extraction", meta=(AllowPrivateAccess="true", BindWidget))
	UVerticalBox* ExtractionPointList;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Extraction", meta=(AllowPrivateAccess="true"))
	TArray<UExtractionPointWidget*> ExtractionPointWidgets;
};
