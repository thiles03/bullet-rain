#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BR_Grenade.generated.h"

class ABR_CharacterEnemy;
class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class BULLETRAIN_API ABR_Grenade : public AActor
{
	GENERATED_BODY()
	
public:	
	//CONSTRUCTOR
	ABR_Grenade();

	//FUNCTIONS
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	//COMPONENTS
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USphereComponent *Collider;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USphereComponent *BlastRadius;	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent *StaticMesh;

	//VARIABLES
	UPROPERTY(EditAnywhere)
	FVector ThrowForce = FVector(800.f);
	UPROPERTY(EditAnywhere)
	FVector BlastForce = FVector(5500.f);
	UPROPERTY(EditAnywhere)
	float Fuse = 1.5f;
	UPROPERTY(EditAnywhere)
	float Damage = 200.f;
	FTimerHandle DestroyTimer;
	// Grenade effects
	UPROPERTY(EditAnywhere)
	UParticleSystem *ExplosionEffect;
	UPROPERTY(EditAnywhere)
	USoundBase *ExplosionSound;

	//FUNCTIONS
	UFUNCTION()
	void DestroyActor();
};
