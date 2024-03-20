// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemWidget.generated.h"

class UItemObject;
class UOverlay;
class USizeBox;
class UBorder;
class UImage;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRemovedSignature, UItemObject*, RemovedItem);

/**
 * 
 */
UCLASS()
class JIGSAWINVENTORYSYSTEM_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// TODO: Should probably be private with functions bind/unbind
	UPROPERTY(BlueprintReadWrite, Category="Item Events")
	FOnRemovedSignature OnRemovedEvent;
	
	UFUNCTION(BlueprintCallable, Category="Item Widget")
	void InitializeItem(UItemObject* NewItem, float NewTileSize);
	UFUNCTION(BlueprintCallable, Category="Item Widget")
	void Refresh();

protected:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	
private:
	// May need to change Overlay to CanvasPanel
	UPROPERTY(BlueprintReadOnly, Category="Item Widget", meta=(AllowPrivateAccess="true", BindWidget))
	UOverlay* ItemOverlay;
	UPROPERTY(BlueprintReadOnly, Category="Item Widget", meta=(AllowPrivateAccess="true", BindWidget))
	USizeBox* BackgroundSizeBox;
	UPROPERTY(BlueprintReadOnly, Category="Item Widget", meta=(AllowPrivateAccess="true", BindWidget))
	UBorder* BackgroundBorder;
	UPROPERTY(BlueprintReadOnly, Category="Item Widget", meta=(AllowPrivateAccess="true", BindWidget))
	UImage* ItemIcon;
	UPROPERTY(BlueprintReadOnly, Category="Item Widget", meta=(AllowPrivateAccess="true", ExposeOnSpawn))
	float TileSize = 50.f;
	UPROPERTY(BlueprintReadOnly, Category="Item Widget", meta=(AllowPrivateAccess="true"))
	FLinearColor BackgroundColor = FLinearColor(0.f, 0.f, 0.f, 0.5f);
	UPROPERTY(BlueprintReadOnly, Category="Item Widget", meta=(AllowPrivateAccess="true"))
	FLinearColor HoveredBackgroundColor = FLinearColor(0.5f, 0.5f, 0.5f, 0.5f);
	
	UPROPERTY(BlueprintReadOnly, Category="Item", meta=(AllowPrivateAccess="true", ExposeOnSpawn))
	UItemObject* ItemObject;
	
};
