#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BR_CharacterStats.generated.h"

class ABR_PlayerController;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BULLETRAIN_API UBR_CharacterStats : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBR_CharacterStats();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//SETTERS
	//Armour
	UFUNCTION(BlueprintCallable)
	void SetMaxArmour(float ArmourValue);
	UFUNCTION(BlueprintCallable)
	void UpdateCurrentArmour(float ArmourValue);
	//Health
	UFUNCTION(BlueprintCallable)
	void SetMaxHealth(float HealthValue);
	UFUNCTION(BlueprintCallable)
	void UpdateCurrentHealth(float HealthValue);

	//GETTERS
	//Armour
	UFUNCTION(BlueprintCallable)
	float GetArmourPercent() const;
	//Health
	UFUNCTION(BlueprintCallable)
	float GetHealthPercent() const;

	//FUNCTIONS
	UFUNCTION(BlueprintCallable)
	void TakeDamage(float Damage);
	UFUNCTION(BlueprintCallable)
	void TakeUnblockableDamage(float Damage, float UnblockableDamage);


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:	
	//VARIABLES
	//Armour
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float MaxArmour = 100.0f;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	float CurrentArmour;
	//Health
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float MaxHealth = 100.0f;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	float CurrentHealth;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float HealthRegenRate = .5f;
	//Player controller
	ABR_PlayerController* PlayerController;
};