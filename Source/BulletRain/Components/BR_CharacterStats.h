#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BR_CharacterStats.generated.h"


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
	UFUNCTION(BlueprintCallable)
	void SetArmour(float ArmourValue);
	UFUNCTION(BlueprintCallable)
	void SetHealth(float HealthValue);

	//GETTERS
	UFUNCTION(BlueprintCallable)
	float GetArmour();
	UFUNCTION(BlueprintCallable)
	float GetHealth();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:	
	//VARIABLES
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float Armour = 1.0f;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float Health = 1.0f;
};