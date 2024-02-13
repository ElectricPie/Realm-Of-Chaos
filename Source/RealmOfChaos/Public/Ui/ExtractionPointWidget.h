// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExtractionPointWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class REALMOFCHAOS_API UExtractionPointWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	/**
	 * @brief Sets the extraction point name
	 * @param Text The name of the extraction point
	 */
	UFUNCTION(BlueprintCallable, Category="Extraction")
	void SetPointName(const FText& Text) const;
	/**
	 * @brief Sets the distance to the extraction point rounded to the nearest integer in meters
	 * @param Distance The distance to the extraction point in meters
	 */
	UFUNCTION(BlueprintCallable, Category="Extraction")
	void SetPointDistance(const int32 Distance) const;
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Extraction", meta=(AllowPrivateAccess="true", BindWidget))
	UTextBlock* PointNameText;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Extraction", meta=(AllowPrivateAccess="true", BindWidget))
	UTextBlock* PointDistanceText;
};
