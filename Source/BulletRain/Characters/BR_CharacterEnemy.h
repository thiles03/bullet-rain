#pragma once

#include "CoreMinimal.h"
#include "BR_CharacterBase.h"
#include "BR_CharacterEnemy.generated.h"

class ABR_CharacterStats_Enemy;
class UPawnSensingComponent;

UCLASS()
class BULLETRAIN_API ABR_CharacterEnemy : public ABR_CharacterBase
{
	GENERATED_BODY()

public:
	//CONSTRUCTOR
	ABR_CharacterEnemy();

	//FUNCTIONS
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	//FUNCTIONS
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	//COMPONENTS
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UPawnSensingComponent *PawnSensor;

	//FUNCTIONS
	// On overlap event
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
	// Called when another pawn enters sight line
	UFUNCTION()
	void OnSeePawn(APawn *OtherPawn);
};