// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemActor.h"

#include "Items/ItemObject.h"

// Sets default values
AItemActor::AItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AItemActor::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(ItemObject))
	{
		ItemObject = GetDefaultObject();
	}
}

UItemObject* AItemActor::GetDefaultObject_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("%s has not implemented GetDefaultObject!"), *GetName());
	return nullptr;
}

// Called every frame
void AItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

