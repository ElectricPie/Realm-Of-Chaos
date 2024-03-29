// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemActor.generated.h"

class UItemObject;

UCLASS()
class JIGSAWINVENTORYSYSTEM_API AItemActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemActor();

	UFUNCTION(BlueprintCallable, Category="Item")
	UItemObject* GetItemObject() const { return ItemObject; }
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintNativeEvent)
	UItemObject* GetDefaultObject();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	USceneComponent* Root;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY(BlueprintReadOnly, Category="Item", meta=(AllowPrivateAccess="true"))
	UItemObject* ItemObject;
};
