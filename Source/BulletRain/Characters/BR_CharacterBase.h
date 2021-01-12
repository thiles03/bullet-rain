#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BR_CharacterBase.generated.h"

UCLASS()
class BULLETRAIN_API ABR_CharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// CONSTRUCTOR
	ABR_CharacterBase();

	//FUNCTIONS
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	//FUNCTIONS
	virtual void BeginPlay() override;

private:	

};
