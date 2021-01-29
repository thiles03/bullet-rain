#pragma once

#include "CoreMinimal.h"
#include "BR_CharacterStats_Base.h"
#include "BR_CharacterStats_Player.generated.h"

class ABR_PlayerController;
class UAudioComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BULLETRAIN_API UBR_CharacterStats_Player : public UBR_CharacterStats_Base
{
	GENERATED_BODY()
	
public:	
	//CONSTRUCTOR
	UBR_CharacterStats_Player();

	//Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//SETTERS
	UFUNCTION(BlueprintCallable)
	void SetMaxBulletTime(float TimeValue);
	UFUNCTION(BlueprintCallable)
	void UpdateRemainingBulletTime(float TimeValue);

	//GETTERS
	UFUNCTION(BlueprintCallable)
	float GetRemainingBulletTime() const;
	UFUNCTION(BlueprintCallable)
	bool GetBulletTimeActive() const;

	//FUNCTIONS
	//Damage handlers
	virtual void TakeDamage(float Damage) override;
	virtual void TakeUnblockableDamage(float Damage, float UnblockableDamage) override;
	//Bullet time handler
	void BulletTime();

protected:
	//Called when the game starts
	virtual void BeginPlay() override;

private:	
	//VARIABLES
	//Health regen variables
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float HealthRegenRate = .5f;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float RegenDelay = 5.f;
	bool CanRegenHealth = true;
	FTimerHandle RegenResetTimer;
	//Slow motion time
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	USoundBase *EnterSloMoSound;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	USoundBase *ExitSloMoSound;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	USoundBase *HeartbeatSound;
	UAudioComponent *HeartBeat;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float BulletTimeRegenRate = .4f;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float MaxBulletTime = 5.f;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	float RemainingBulletTime;
	bool CanRegenBulletTime = true;
	bool IsBulletTimeActive = false;
	//Player controller
	ABR_PlayerController* PlayerController;
	// Death timer
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float LoseScreenDelay = 3.f;
	FTimerHandle DeathTimer;

	//FUNCTIONS
	void Damaged();
	void EnableRegen();
	virtual void Die() override;
	void LoseScreen();
};