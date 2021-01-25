#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BR_PickUp_Base.generated.h"

class ABR_CharacterPlayer;
class UCapsuleComponent;
class UStaticMeshComponent;

UCLASS()
class BULLETRAIN_API ABR_PickUp_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	//CONSTRUCTOR
	ABR_PickUp_Base();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Overlap event
	UFUNCTION() 
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

protected:
	//VARIABLES
	// Pickup sound
	UPROPERTY(EditAnywhere)
	USoundBase *PickupSound;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:	
	//COMPONENTS
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent *CapsuleCollider;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent *StaticMesh;
};
