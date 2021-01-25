#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BR_CharacterBase.generated.h"

UCLASS()
class BULLETRAIN_API ABR_CharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// CONSTRUCTOR
	ABR_CharacterBase();

	//FUNCTIONS
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
protected:
	//VARIABLES
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MaxSpeed = 600.f;

	//FUNCTIONS
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// On hit event
	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	//Set movement speed
	void SetSpeed(float Speed);

private:	
	//FUNCTIONS
};
