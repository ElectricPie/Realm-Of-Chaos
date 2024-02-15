// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TopDownPlayerController.generated.h"

class UExtractionPlayerHud;
class AExtractionPoint;
class UInputAction;
class APlayerCharacter;
class UInputMappingContext;
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class REALMOFCHAOS_API ATopDownPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void AuthSetExtractionPoints(TArray<const AExtractionPoint*> NewExtractionPoints);

	const TArray<const AExtractionPoint*>& GetExtractionPoints() const { return ExtractionPoints; }
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupInputComponent() override;
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* MappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess = "true"))
	float RaycastLimit = 3000.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI", meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UExtractionPlayerHud> ExtractionHudClass;
	UPROPERTY(BlueprintReadOnly, Category="UI", meta=(AllowPrivateAccess="true"))
	UExtractionPlayerHud* Hud;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI", meta=(AllowPrivateAccess="true"))
	float ExtractionPointsHudUpdateInterval = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI", meta=(AllowPrivateAccess="True", ClampMin="0.0", UIMin="0.0",
		ToolTip="The distance to the extraction point is multiplied by this value"))
	float DistanceToExtractionPointModifier = 0.01f;
	
	UPROPERTY()
	APlayerCharacter* PlayerCharacter;
	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_ExtractionPoints)
	TArray<const AExtractionPoint*> ExtractionPoints;

	
	bool bResetPointUi;
	FTimerHandle ExtractionPointsHudUpdateTimer;
	
	void Move(const FInputActionValue& Value);
	void RotateToTarget(FVector TargetLocation);

	UFUNCTION()
	void OnRep_ExtractionPoints();
	
	void UpdateExtractionPointsUI();
};
