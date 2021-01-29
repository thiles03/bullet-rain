#pragma once

#include "CoreMinimal.h"
#include "BR_CombatHandler_Base.h"
#include "BR_CombatHandler_Enemy.generated.h"

class ABR_CharacterPlayer;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BULLETRAIN_API UBR_CombatHandler_Enemy : public UBR_CombatHandler_Base
{
	GENERATED_BODY()

public:	
	//CONSTRUCTOR
	UBR_CombatHandler_Enemy();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//GETTERS
	UFUNCTION(BlueprintCallable)
	bool GetIsAttacking() const;

	//SETTERS
	UFUNCTION(BlueprintCallable)
	void SetIsAttacking(bool Attacking);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:	
	//FUNCTIONS
	void Attack();

	//VARIABLES
	// Reference to player
	UPROPERTY()
	ABR_CharacterPlayer* Player;
	UPROPERTY(VisibleAnywhere)
	bool IsAttacking = false;
	// SFX & VFX
	UPROPERTY(EditAnywhere)
	USoundBase* MinionSound;
	UPROPERTY(EditAnywhere)
	USoundBase* ImpactSound;
};
