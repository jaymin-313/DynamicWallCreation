// Fill out your copyright notice in the Description page of Project Settings.


#include "WallWidget.h"

void UWallWidget::UpdateTopRightText(const FString& NewText)
{
    if (TopRightTextBlock)
    {
        TopRightTextBlock->SetText(FText::FromString(NewText));
    }
}

void UWallWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (TopRightTextBlock)
    {
        GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Silver, TEXT("Adding text to viewport"));
        //TopRightTextBlock->SetPositionInViewport(FVector2D(0.8f, 0.05f), false);
        TopRightTextBlock->SetText(FText::FromString("Your\nMultiple\nLines\nOf\nText"));
        TopRightTextBlock->AddToRoot();
        // Optionally, set font and color properties here if needed
    }
}
