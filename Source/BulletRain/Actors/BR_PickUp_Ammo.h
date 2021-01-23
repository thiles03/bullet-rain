#pragma once

#include "CoreMinimal.h"
#include "BR_PickUp_Base.h"
#include "BR_PickUp_Ammo.generated.h"

UCLASS()
class BULLETRAIN_API ABR_PickUp_Ammo : public ABR_PickUp_Base
{
	GENERATED_BODY()
	
public:	
	//CONSTRUCTOR
	ABR_PickUp_Ammo();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	

};
