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

	//FUNCTIONS
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// Weapons
	void Fire(EPistol Pistol);
	void Reload(EPistol Pistol);
	// Ammo
	UFUNCTION(BlueprintCallable)
	int GetWeaponAmmo(EPistol Pistol) const;
	UFUNCTION(BlueprintCallable)
	int GetCarriedAmmo() const;
	UFUNCTION(BlueprintCallable)
	void SetAmmoCapacity(int Capacity);
	UFUNCTION(BlueprintCallable)
	void SetMagCapacity(int Capacity);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	//VARIABLES
	//Ammunition properties
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABR_Projectile> ProjectileClass;
	UPROPERTY(EditAnywhere)
	float Range = 1300.f;
	UPROPERTY(EditAnywhere)
	int MaxMagAmmo = 17;
	UPROPERTY(EditAnywhere)
	int MaxCarriedAmmo = 100;
	UPROPERTY(VisibleAnywhere)
	int CurrentCarriedAmmo = 40;
	UPROPERTY(VisibleAnywhere)
	int AmmoLeft;
	UPROPERTY(VisibleAnywhere)
	int AmmoRight;
	//Visuals
	UPROPERTY(EditAnywhere)
	UParticleSystem *MuzzleFlash;
	UPROPERTY(EditAnywhere)
	UParticleSystem *ImpactEffect;
	//Sounds
	UPROPERTY(EditAnywhere)
	USoundBase *MuzzleSound;
	UPROPERTY(EditAnywhere)
	USoundBase *ImpactSound;

	//FUNCTIONS
	//Locate crosshair vanishing point
	FVector GetAimPoint() const;
};
