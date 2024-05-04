// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WallSpline.h"
#include "WallWidget.h"
#include "GameFramework/PlayerController.h"
#include "Components/SplineComponent.h"
#include "WallBuilderController.generated.h"

DECLARE_DELEGATE_OneParam(FShowTextDelegate, FString);
UCLASS()
class DYNAMICWALLS_API AWallBuilderController : public APlayerController
{
	GENERATED_BODY()
public:

    AWallBuilderController();
    // Enable the cursor and set input mode to game and UI
    UFUNCTION(BlueprintCallable)
    void EnableCursor();

    void BeginPlay();

    // Disable the cursor and set input mode to game only
    UFUNCTION(BlueprintCallable)
    void DisableCursor();

    // Input bindings for left mouse button press/release
    virtual void SetupInputComponent() override;
    void OnLeftMouseButtonPressed();
    void OnRightMouseButtonPressed();

    void UndoWall();

    void DeleteWall();

    void ClearWalls();


    FShowTextDelegate ShowText;

private:
    TArray<AWallSpline*> WallSplineActor;
};
