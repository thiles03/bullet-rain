#pragma once

#include "CoreMinimal.h"
#include "BR_PickUp_Base.h"
#include "BR_PickUp_BulletTime.generated.h"

class ABR_CharacterPlayer;
class UBR_CombatHandler_Player;

UCLASS()
class BULLETRAIN_API ABR_PickUp_BulletTime : public ABR_PickUp_Base
{
	GENERATED_BODY()
	
public:	
	//CONSTRUCTOR
	ABR_PickUp_BulletTime();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	//VARIABLES
	UPROPERTY(Editanywhere, meta = (AllowPrivateAccess = "true"))
	float BulletTimeValue = 30;

	//FUNCTIONS
	// Overlap event	
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;
};
