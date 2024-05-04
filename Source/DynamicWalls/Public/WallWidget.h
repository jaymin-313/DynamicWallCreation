// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include "WallWidget.generated.h"

/**
 * 
 */
UCLASS()
class DYNAMICWALLS_API UWallWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
    UPROPERTY(meta = (BindWidget))
    UTextBlock* TopRightTextBlock;

public:
    UFUNCTION(BlueprintImplementableEvent)
    void UpdateText(const FString& NewText);
    UFUNCTION(BlueprintCallable)
    void UpdateTopRightText(const FString& NewText);

protected:
    virtual void NativeConstruct() override;
};
