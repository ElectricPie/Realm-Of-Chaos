// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TopDownPlayerController.generated.h"

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

	UPROPERTY()
	APlayerCharacter* PlayerCharacter;
	UPROPERTY(VisibleAnywhere, Replicated)
	TArray<const AExtractionPoint*> ExtractionPoints;

	void Move(const FInputActionValue& Value);
	void RotateToTarget(FVector TargetLocation);
};
