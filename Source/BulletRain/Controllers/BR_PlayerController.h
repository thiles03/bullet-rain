#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BR_PlayerController.generated.h"

class UUserWidget;

UCLASS()
class BULLETRAIN_API ABR_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	//FUNCTIONS
	void CreateDamageVignette();
	void CreateSloMoVignette();
	void CreateHitMarker();
	void CreateCustomWidget(TSubclassOf<UUserWidget> Widget);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;	

private:
	//VARIABLES
	UPROPERTY(EditDefaultsOnly, Category = "User Interface", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> HUDClass;
	UPROPERTY(EditDefaultsOnly, Category = "User Interface", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> CrossHairClass;	
	UPROPERTY(EditDefaultsOnly, Category = "User Interface", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> DamageVignetteClass;
	UPROPERTY(EditDefaultsOnly, Category = "User Interface", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> SloMoVignetteClass;
	UPROPERTY(EditDefaultsOnly, Category = "User Interface", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> HitMarkerClass;	
	UPROPERTY(EditDefaultsOnly, Category = "User Interface", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> WinScreenClass;
	UPROPERTY(EditDefaultsOnly, Category = "User Interface", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> LoseScreenClass;

	UUserWidget* HUDWidget;
	UUserWidget* CrossHairWidget;

	//FUNCTIONS
};
