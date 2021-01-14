#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BR_PlayerController.generated.h"

class UUserWidget;

UCLASS()
class BULLETRAIN_API ABR_PlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;	

private:
	//VARIABLES
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> HUDClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> WinScreenClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> LoseScreenClass;

	UUserWidget* CurrentWidget;
};
