#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "BulletRain/BR_Enums.h"
#include "BR_CharacterBase.h"
#include "BR_CharacterPlayer.generated.h"

class UBR_CombatHandler_Player;
class UCameraComponent;

UCLASS()
class BULLETRAIN_API ABR_CharacterPlayer : public ABR_CharacterBase
{
	GENERATED_BODY()

public:
	//CONSTRUCTOR
	ABR_CharacterPlayer();

	//COMPONENTS
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent *Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UBR_CombatHandler_Player *CombatHandler;

	//FUNCTIONS
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	//FUNCTIONS
	virtual void BeginPlay() override;

private:
	//COMPONENTS
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Aiming", meta = (AllowPrivateAccess = "true"))
	UCurveFloat *fCurve;

	//VARIABLES
	//Movement
	UPROPERTY(VisibleAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float CurrentRotationRate;
	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float BaseRotationRate = 50.f;
	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float AimRotationRate = 30.f;
	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float SprintRotationRate = 20.f;
	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float SprintSpeed = 1000.f;
	UPROPERTY(VisibleAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	bool IsSprinting = false;

	//Aiming
	FTimeline FOVTimeline;
	FOnTimelineFloat TimelineProgress;
	UPROPERTY(VisibleAnywhere, Category = "Aiming", meta = (AllowPrivateAccess = "true"))
	float FOV;
	UPROPERTY(VisibleAnywhere, Category = "Aiming", meta = (AllowPrivateAccess = "true"))
	float AimFOV;	
	UPROPERTY(EditAnywhere, Category = "Aiming", meta = (AllowPrivateAccess = "true"))
	float FOVOffset = 40.f;
	UPROPERTY(EditAnywhere, Category = "Aiming", meta = (AllowPrivateAccess = "true"))
	float AimMoveSpeed = 300.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Aiming", meta = (AllowPrivateAccess = "true"))
	bool IsAiming = false;

	//FUNCTIONS
	//Movement
	void LookRight(float AxisValue); //Gamepad
	void LookUp(float AxisValue); //Gamepad
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void Sprint();
	void SprintReset();
	void ToggleCrouch();

	//Combat
	void Fire(EPistol Pistol);
	void Reload(EPistol Pistol);

	//Aiming
	void Aim();
	void AimReset();
	void SetupTimeline();
	UFUNCTION()
	void TimelineFloatReturn(float Value);	
};
