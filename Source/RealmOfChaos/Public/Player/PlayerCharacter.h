// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class USphereComponent;
class USpringArmComponent;
class UCameraComponent;
class UInventoryComponent;
class AItemActor;

UCLASS()
class REALMOFCHAOS_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();
	
	void Move(FVector Direction);

	UFUNCTION(BlueprintCallable)
	bool IsMovingForward() const;

	UFUNCTION(BlueprintCallable, Category="Inventory")
	UInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess="true", ToolTip="Adjusts how fast the character moves in any direction"))
	float SpeedModifier = 0.8f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess="true", ToolTip="Adjusts how fast the character moves when moving backwards"))
	float BackwardsSpeedModifier = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess="true", ToolTip="How far from forward the character can move before they are considered to be moving backwards", ClampMin="-1.0", ClampMax="1.0", UIMin="-1.0", UIMax="1.0"))
	float BackwardsThreshold = -0.5f;

	TArray<int32> ActiveExtractionPoints;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Inventory", meta=(AllowPrivateAccess="true"))
	UInventoryComponent* InventoryComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Inventory", meta=(AllowPrivateAccess="true"))
	USphereComponent* GroundItemsDetectionSphere;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Inventory", meta=(AllowPrivateAccess="true"))
	TArray<AItemActor*> NearbyItems;
};
