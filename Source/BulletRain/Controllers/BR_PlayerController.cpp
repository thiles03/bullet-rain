#include "BR_PlayerController.h"
#include "Blueprint/UserWidget.h"


void ABR_PlayerController::BeginPlay() 
{
    Super::BeginPlay();
    
    CurrentWidget = CreateWidget(this, HUDClass);
    if (CurrentWidget)
    {
        CurrentWidget->AddToViewport();
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
