// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExtractionPoint.generated.h"

class APlayerCharacter;
UCLASS()
class REALMOFCHAOS_API AExtractionPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExtractionPoint();

	FName GetPointName() const { return PointName; }
	float GetExtractionTime() const { return ExtractionTime; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Extraction Settings", meta=(AllowPrivateAccess="true"))
	FName PointName = FName(TEXT("Not Set"));
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Extraction Settings", meta=(AllowPrivateAccess="true",
		ToolTip="How long a player needs to remain in the point to extract", ClampMin=0.f, UIMin=0.f))
	float ExtractionTime = 10.f;
};
