#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BR_CombatHandler_Base.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BULLETRAIN_API UBR_CombatHandler_Base : public UActorComponent
{
	GENERATED_BODY()

public:	
	//CONSTRUCTOR
	UBR_CombatHandler_Base();

	//FUNCTIONS
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	//GETTERS
	float GetAttackDamage();
	float GetAttackSpeed();
	float GetAttackRange();

protected:
	//VARIABLES
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float AttackDamage = 5.f;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float AttackSpeed = 5.f;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float AttackRange = 50.f;

	//FUNCTIONS
	// Called when the game starts
	virtual void BeginPlay() override;

private:	


		
};
