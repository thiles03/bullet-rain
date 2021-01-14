#pragma once

#include "CoreMinimal.h"
#include "BR_CharacterBase.h"
#include "BR_CharacterPlayer.generated.h"

UCLASS()
class BULLETRAIN_API ABR_CharacterPlayer : public ABR_CharacterBase
{
	GENERATED_BODY()

public:
	//CONSTRUCTOR
	ABR_CharacterPlayer();

	//FUNCTIONS
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	//FUNCTIONS
	virtual void BeginPlay() override;

private:
	//FUNCTIONS
	//Movement
	void LookRight(float AxisValue); //Gamepad
	void LookUp(float AxisValue); //Gamepad
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	//VARIABLES
	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float RotationRate = 50.f;
};