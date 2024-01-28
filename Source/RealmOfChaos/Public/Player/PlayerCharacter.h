// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class REALMOFCHAOS_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()



public:
	// Sets default values for this character's properties
	APlayerCharacter();
	
	UFUNCTION(Server, Unreliable)
	void ServerUpdateRotation(FRotator NewRotation);
	
	void FaceDirection(const FVector LookTarget);

	void Move(FVector Direction);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, Category="Components")
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, Category="Components")
	UCameraComponent* Camera;
};
