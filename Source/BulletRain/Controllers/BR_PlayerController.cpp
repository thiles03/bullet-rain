#include "BR_PlayerController.h"
#include "Blueprint/UserWidget.h"

void ABR_PlayerController::BeginPlay()
{
    Super::BeginPlay();

    HUDWidget = CreateWidget(this, HUDClass);
    CrossHairWidget = CreateWidget(this, CrossHairClass);
    if (HUDWidget && CrossHairWidget)
    {
        HUDWidget->AddToViewport();
        CrossHairWidget->AddToViewport();
    }
}

void ABR_PlayerController::CreateDamageVignette()
{
    UUserWidget *DamageVignette = CreateWidget(this, DamageVignetteClass);
    if (DamageVignette)
    {
        DamageVignette->AddToViewport();
    }
}

void ABR_PlayerController::CreateSloMoVignette()
{
    UUserWidget *SloMoVignette = CreateWidget(this, SloMoVignetteClass);
    if (SloMoVignette)
    {
        SloMoVignette->AddToViewport();
    }
}

void ABR_PlayerController::CreateHitMarker() 
{
    UUserWidget *HitMarker = CreateWidget(this, HitMarkerClass);
    if (HitMarker)
    {
        HitMarker->AddToViewport();
    }
}

void ABR_PlayerController::CreateLoseScreen() 
{
    UUserWidget *LoseScreen = CreateWidget(this, LoseScreenClass);
    if (LoseScreen)
    {
        LoseScreen->AddToViewport();
    }
}

void ABR_PlayerController::CreateCustomWidget(TSubclassOf<UUserWidget> Widget) 
{
    UUserWidget *CustomWidget = CreateWidget(this, Widget);
    if (CustomWidget)
    {
        CustomWidget->AddToViewport();
    }
}