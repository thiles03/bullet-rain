#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BR_Projectile.generated.h"

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

	//VARIABLES
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	float Damage;
	
	//FUNCTIONS
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
