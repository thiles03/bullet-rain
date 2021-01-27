#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BR_Projectile.generated.h"

class ABR_CharacterPlayer;
class USphereComponent;
class UStaticMeshComponent;
class UProjectileMovementComponent;
class USceneComponent;

UCLASS()
class BULLETRAIN_API ABR_Projectile : public AActor
{
	GENERATED_BODY()

public:
	//CONSTRUCTOR
	ABR_Projectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Get damage
	float GetDamage();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	//COMPONENTS
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USphereComponent *Collider;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent *StaticMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent *ProjectileMovement;
	//Bullet effects
	UPROPERTY(EditAnywhere)
	UParticleSystem *ImpactEffect;
	UPROPERTY(EditAnywhere)
	USoundBase *ImpactSoundEnemy;
	UPROPERTY(EditAnywhere)
	USoundBase *ImpactSoundWorld;

	//VARIABLES
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	float Damage;
	UPROPERTY(EditAnywhere)
	float LifeTime = 5.f;
	FTimerHandle DestroyTimer;

	//FUNCTIONS
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void DestroyActor();
};
