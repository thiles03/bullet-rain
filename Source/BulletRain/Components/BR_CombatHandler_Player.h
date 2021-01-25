#pragma once

#include "CoreMinimal.h"
#include "BulletRain/BR_Enums.h"
#include "BR_CombatHandler_Base.h"
#include "BR_CombatHandler_Player.generated.h"

class ABR_Projectile;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BULLETRAIN_API UBR_CombatHandler_Player : public UBR_CombatHandler_Base
{
	GENERATED_BODY()

public:
	//CONSTRUCTOR
	UBR_CombatHandler_Player();

	//FUNCTIONS
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	// Weapons
	void Fire(EPistol Pistol);
	void Reload(EPistol Pistol);
	//GETTERS
	UFUNCTION(BlueprintCallable)
	int GetWeaponAmmo(EPistol Pistol) const;
	UFUNCTION(BlueprintCallable)
	int GetCarriedAmmo() const;
	UFUNCTION(BlueprintCallable)
	bool GetIsReloading();
	//SETTERS
	UFUNCTION(BlueprintCallable)
	void SetMaxCarriedAmmo(int Capacity);
	UFUNCTION(BlueprintCallable)
	void SetCurrentCarriedAmmo(int Amount);
	UFUNCTION(BlueprintCallable)
	void SetMaxMagAmmo(int Capacity);
	UFUNCTION(BlueprintCallable)
	void SetIsReloading(EPistol Pistol, bool Reloading);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	//VARIABLES
	//Weapon/ammo properties
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
	//Reload handling
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float ReloadSpeed = 3.f;
	UPROPERTY(VisibleAnywhere)
	bool IsReloadingLeft = false;
	UPROPERTY(VisibleAnywhere)
	bool IsReloadingRight = false;
	FTimerHandle ReloadTimerLeft;
	FTimerDelegate ReloadDelegateLeft;
	FTimerHandle ReloadTimerRight;
	FTimerDelegate ReloadDelegateRight;
	//Weapon effects
	UPROPERTY(EditAnywhere)
	UParticleSystem *MuzzleFlash;
	UPROPERTY(EditAnywhere)
	USoundBase *MuzzleSound;
	UPROPERTY(EditAnywhere)
	USoundBase *BulletSound;
	UPROPERTY(EditAnywhere)
	USoundBase *EmptyClick;
	UPROPERTY(EditAnywhere)
	USoundBase *ReloadSound;

	//FUNCTIONS
	//Locate crosshair vanishing point
	FVector GetAimPoint() const;
};
