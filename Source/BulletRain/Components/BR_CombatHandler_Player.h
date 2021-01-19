#pragma once

#include "CoreMinimal.h"
#include "BulletRain/BR_Enums.h"
#include "BR_CombatHandler_Base.h"
#include "BR_CombatHandler_Player.generated.h"

class ABR_Projectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BULLETRAIN_API UBR_CombatHandler_Player : public UBR_CombatHandler_Base
{
	GENERATED_BODY()

public:	
	//CONSTRUCTOR
	UBR_CombatHandler_Player();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Fire weapons
	void Fire(EPistol Pistol);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	//VARIABLES
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABR_Projectile> ProjectileClass;
};
