#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BR_AIController.generated.h"

class ABR_CharacterEnemy;

UCLASS()
class BULLETRAIN_API ABR_AIController : public AAIController
{
	GENERATED_BODY()
	
public:
	//FUNCTIONS
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Move to given location
	void Patrol();
	void MoveToAttack(FVector Location, float Range);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	//VARIABLES
	// Reference to this controller's character
	UPROPERTY()
	ABR_CharacterEnemy* EnemyCharacter;
	// Patrol timer
	UPROPERTY(EditAnywhere)
	float PatrolDelay = 5.f;
	UPROPERTY(EditAnywhere)
	float PatrolRadius = 10000.f;
	UPROPERTY(EditAnywhere)
	float ResetVisibiltyDelay = .5f;
	FTimerHandle PatrolTimer;
	FTimerHandle VisibilityTimer;

	//FUNCTIONS
	UFUNCTION()
	void ResetPlayerVisible();

};
