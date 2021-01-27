#pragma once

#include "CoreMinimal.h"
#include "BulletRain/BR_Enums.h"
#include "BR_CombatHandler_Base.h"
#include "BR_CombatHandler_Player.generated.h"

class ABR_Projectile;
class ABR_Grenade;

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
	void ThrowGrenade();

	//GETTERS
	UFUNCTION(BlueprintCallable)
	int GetWeaponAmmo(EPistol Pistol) const;
	UFUNCTION(BlueprintCallable)
	int GetCarriedAmmo() const;
	UFUNCTION(BlueprintCallable)
	int GetCurrentGrenades() const;
	UFUNCTION(BlueprintCallable)
	bool GetIsReloading() const;
	UFUNCTION(BlueprintCallable)
	bool GetIsAttackingRight() const;
	UFUNCTION(BlueprintCallable)
	bool GetIsAttackingLeft() const;

	//SETTERS
	UFUNCTION(BlueprintCallable)
	void SetMaxCarriedAmmo(int Capacity);
	UFUNCTION(BlueprintCallable)
	void SetCurrentCarriedAmmo(int Amount);
	UFUNCTION(BlueprintCallable)
	void SetCurrentGrenades(int Amount);
	UFUNCTION(BlueprintCallable)
	void SetMaxGrenades(int Amount);
	UFUNCTION(BlueprintCallable)
	void SetMaxMagAmmo(int Capacity);
	UFUNCTION(BlueprintCallable)
	void SetIsReloading(EPistol Pistol, bool Reloading);
	UFUNCTION(BlueprintCallable)
	void SetIsAttackingRight(bool Attacking);
	UFUNCTION(BlueprintCallable)
	void SetIsAttackingLeft(bool Attacking);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	//VARIABLES
	//Weapon/ammo properties
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABR_Projectile> ProjectileClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABR_Grenade> GrenadeClass;
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
	UPROPERTY(EditAnywhere)
	int MaxGrenades = 3;
	UPROPERTY(VisibleAnywhere)
	int CurrentGrenades;
	UPROPERTY(EditAnywhere)
	FVector GrenadeOffset = FVector(300.f, 0.f, 0.f);
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
	// Player mesh
	UPROPERTY()
	USkeletalMeshComponent* PlayerMesh;
	// Is the player attacking
	UPROPERTY(VisibleAnywhere)
	bool IsAttackingLeft = false;
	UPROPERTY(VisibleAnywhere)
	bool IsAttackingRight = false;

	//FUNCTIONS
	//Locate crosshair vanishing point
	FVector GetAimPoint() const;
};
