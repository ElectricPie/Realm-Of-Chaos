// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryGridWidget.generated.h"

class UInventoryComponent;
class USizeBox;
class UCanvasPanel;

USTRUCT(BlueprintType)
struct FLine
{
	GENERATED_BODY()

	FLine(): Start(FVector2D::ZeroVector), End(FVector2D::ZeroVector)
	{
	}
	FLine(const FVector2D& Start, const FVector2D& End): Start(Start), End(End)
	{
	}
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Line")
	FVector2D Start;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Line")
	FVector2D End;
};

/**
 * 
 */
UCLASS()
class JIGSAWINVENTORYSYSTEM_API UInventoryGridWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	// TODO: Switch columns and rows for inventory component
	UFUNCTION(BlueprintCallable, Category="Grid")
	void InitializeGrid(const UInventoryComponent* NewInventoryComponent, const float NewTileSize = 50.f);

protected:
	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Widgets", meta=(AllowPrivateAccess="true", BindWidget))
	USizeBox* GridSizeBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Widgets", meta=(AllowPrivateAccess="true", BindWidget))
	UCanvasPanel* GridCanvasPanel; // Look into alternatives?

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Grid Drawing", meta=(AllowPrivateAccess="true"))
	float TileSize = 50.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Grid Drawing", meta=(AllowPrivateAccess="true"))
	FLinearColor GridLineColor = FLinearColor(0.f, 0.f, 0.f, 0.5f);
	UPROPERTY(BlueprintReadOnly, Category="Grid Drawing", meta=(AllowPrivateAccess="true"))
	TArray<FLine> GridLines;

	UPROPERTY(BlueprintReadOnly, Category="Grid Drawing", meta=(AllowPrivateAccess="true"))
	const UInventoryComponent* InventoryComponent;
};
