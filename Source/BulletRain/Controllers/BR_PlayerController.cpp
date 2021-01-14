#include "BR_PlayerController.h"
#include "Blueprint/UserWidget.h"


void ABR_PlayerController::BeginPlay() 
{
    Super::BeginPlay();
    
    CurrentWidget = CreateWidget(this, PlayerHUDClass);
    if (CurrentWidget)
    {
        CurrentWidget->AddToViewport();
    }
}
