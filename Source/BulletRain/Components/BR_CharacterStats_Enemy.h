#pragma once

#include "CoreMinimal.h"
#include "BR_CharacterStats_Base.h"
#include "BR_CharacterStats_Enemy.generated.h"

class ABR_PlayerController;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BULLETRAIN_API UBR_CharacterStats_Enemy : public UBR_CharacterStats_Base
{
	GENERATED_BODY()
	
public:	
	//CONSTRUCTOR
	UBR_CharacterStats_Enemy();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// Damage handlers
	virtual void TakeDamage(float Damage) override;
	virtual void TakeUnblockableDamage(float Damage, float UnblockableDamage) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	//VARIABLES
	//Player controller
	ABR_PlayerController* PlayerController;

	//FUNCTIONS
	// Death handler
	virtual void Die() override;
};
