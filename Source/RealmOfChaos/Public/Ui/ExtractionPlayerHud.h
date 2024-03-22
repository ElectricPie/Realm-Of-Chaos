// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ExtractionPlayerHud.generated.h"

class UExtractionPlayerHudWidget;

USTRUCT(BlueprintType)
struct FExtractionPointLocation
{
	GENERATED_BODY()

	FExtractionPointLocation() = default;
	FExtractionPointLocation(FName InName, FVector InLocation)
		: Name(InName), Location(InLocation) {}
	
	FName Name;
	FVector Location;
};

/**
 * 
 */
UCLASS(HideDropdown)
class REALMOFCHAOS_API AExtractionPlayerHud : public AHUD
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Extraction Points")
	void ResetExtractionPoints();
	UFUNCTION(BLueprintCallable)
	UExtractionPlayerHudWidget* GetHud() const { return Hud; }
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Extraction Points", meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UExtractionPlayerHudWidget> ExtractionHudClass;
	UPROPERTY(BlueprintReadOnly, Category="Extraction Points", meta=(AllowPrivateAccess="true"))
	UExtractionPlayerHudWidget* Hud;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Extraction Points", meta=(AllowPrivateAccess="true"))
	float ExtractionPointsHudUpdateInterval = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Extraction Points", meta=(AllowPrivateAccess="True", ClampMin="0.0", UIMin="0.0",
	ToolTip="The distance to the extraction point is multiplied by this value"))
	float DistanceToExtractionPointModifier = 0.01f;

	bool bResetExtractionPoints = true;
	FTimerHandle ExtractionPointsHudUpdateTimer;
	
	UFUNCTION()
	void UpdateExtractionPointsDistance();
};
