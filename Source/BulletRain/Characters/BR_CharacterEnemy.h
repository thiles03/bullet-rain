#pragma once

#include "CoreMinimal.h"
#include "BR_CharacterBase.h"
#include "BR_CharacterEnemy.generated.h"

class ABR_AIController;
class UBR_CharacterStats_Enemy;
class UBR_CombatHandler_Enemy;
class UPawnSensingComponent;

UCLASS()
class BULLETRAIN_API ABR_CharacterEnemy : public ABR_CharacterBase
{
	GENERATED_BODY()

public:
	//CONSTRUCTOR
	ABR_CharacterEnemy();

	//COMPONENTS
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UPawnSensingComponent *PawnSensor;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UBR_CombatHandler_Enemy *CharacterCombatHandler;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UBR_CharacterStats_Enemy *CharacterStats;

	//FUNCTIONS
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//GETTERS
	bool GetIsPlayerVisible();

	// SETTERS
	void SetIsPlayerVisible(bool IsVisible);

protected:
	//FUNCTIONS
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	//VARIABLES
	// Reference to this character's AI controller
	UPROPERTY()
	ABR_AIController *AIController;
	// Is the player within sight line
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"));
	bool IsPlayerVisible = false;

	//FUNCTIONS
	// On overlap event
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;
	// Called when another pawn enters sight line
	UFUNCTION()
	void OnSeePawn(APawn *OtherPawn);
	// Rotate character to look at location
	void LookAtTarget(FVector LookAtTarget);
};