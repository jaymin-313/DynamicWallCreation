// Fill out your copyright notice in the Description page of Project Settings.


#include "WallBuilderController.h"
#include "Kismet/GameplayStatics.h"
#include "WallSpline.h"
#include "WallWidget.h"

#include "Engine/Engine.h"


AWallBuilderController::AWallBuilderController()
{
    bShowMouseCursor = true;
}

void AWallBuilderController::EnableCursor()
{
    bShowMouseCursor = true;
    FInputModeGameAndUI InputMode;
    SetInputMode(InputMode);
}

void AWallBuilderController::BeginPlay()
{
    Super::BeginPlay();
    UWallWidget* WallWidget = NewObject<UWallWidget>();

    // Add the widget to the viewport
    if (WallWidget)
    {
        WallWidget->AddToViewport();
    }
    // Spawn or get a reference to the WallSplineActor
    WallSplineActor.Add(NewObject<AWallSpline>(this));
    if (!WallSplineActor[0])
    {
        GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("Failed to Spawn WallSplineActor"));
    }

    ShowText.BindUFunction(this,"ShowWallWidget");
}
void AWallBuilderController::DisableCursor()
{
    bShowMouseCursor = false;
    FInputModeGameOnly InputMode;
    SetInputMode(InputMode);
}

void AWallBuilderController::SetupInputComponent()
{
    Super::SetupInputComponent();

    // Bind left mouse button press/release events
    InputComponent->BindAction("LeftMouseClick", IE_Pressed, this, &AWallBuilderController::OnLeftMouseButtonPressed);
    InputComponent->BindAction("RightMouseClick", IE_Pressed, this, &AWallBuilderController::OnRightMouseButtonPressed);
    InputComponent->BindAction("UndoWall", IE_Pressed, this, &AWallBuilderController::UndoWall);
    InputComponent->BindAction("DeleteWall", IE_Released, this, &AWallBuilderController::DeleteWall);
    InputComponent->BindAction("ClearScreen", IE_Released, this, &AWallBuilderController::ClearWalls);
}

void AWallBuilderController::OnLeftMouseButtonPressed()
{

    FHitResult HitResult;
    GetHitResultUnderCursor(ECC_Visibility, true, HitResult);

    if (HitResult.bBlockingHit)
    {
        FVector ClickLocation = HitResult.Location;

        if (WallSplineActor[WallSplineActor.Num() - 1]->SplineComponent->GetNumberOfSplinePoints() == 1) {
            ShowText.ExecuteIfBound("Wall Creation started");
        }
        WallSplineActor[WallSplineActor.Num()-1]->OnLeftMouseButtonPressed(ClickLocation);
        //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Click Location: %s"), *ClickLocation.ToString()));

    }
}

void AWallBuilderController::OnRightMouseButtonPressed()
{   
    if(WallSplineActor.Num()>0){
        ShowText.ExecuteIfBound("Wall Creation Completed");

    }
    WallSplineActor.Add(NewObject<AWallSpline>(this));
    //GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("Now you can create new wall segment"));
}

void AWallBuilderController::UndoWall() {
    int LastIndex = WallSplineActor[WallSplineActor.Num() - 1]->SplineComponent->GetNumberOfSplinePoints() - 1;
    if (LastIndex > 0) {
        //GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Emerald, TEXT("Undo Logic Triggered"));
        WallSplineActor[WallSplineActor.Num() - 1]->Undo();
    }
    else {
        //GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Emerald, TEXT("No More Points To Undo"));
        ShowText.ExecuteIfBound("No More Points");
        WallSplineActor[WallSplineActor.Num() - 1]->SplineComponent->ClearSplinePoints();
    }
}
void AWallBuilderController::DeleteWall() {
    //GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Emerald, TEXT("Delete Logic Triggered"));
    int CurrentWallSplineObject = WallSplineActor[WallSplineActor.Num() - 1]->Destroy();
    WallSplineActor[WallSplineActor.Num() - 1]->SplineComponent->ClearSplinePoints();
    WallSplineActor.RemoveAt(WallSplineActor.Num() - 1);
    if (WallSplineActor.Num() == 0) {
        WallSplineActor.Add(NewObject<AWallSpline>(this));
    }

}
void AWallBuilderController::ClearWalls() {
    for (int i = 0; i < WallSplineActor.Num() - 1; i++) {
        int CurrentWallSplineObject = WallSplineActor[i]->Destroy();
        WallSplineActor[i]->SplineComponent->ClearSplinePoints();
    }
    WallSplineActor.Empty();
    WallSplineActor.Add(NewObject<AWallSpline>(this));
}