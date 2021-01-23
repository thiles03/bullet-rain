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
    UUserWidget* DamageVignette = CreateWidget(this, DamageVignetteClass);
    if (DamageVignette)
    {
        DamageVignette->AddToViewport();
    }
}
