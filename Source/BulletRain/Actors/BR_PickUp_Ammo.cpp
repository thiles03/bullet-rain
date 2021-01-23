#include "BR_PickUp_Ammo.h"

// Constructor
ABR_PickUp_Ammo::ABR_PickUp_Ammo()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABR_PickUp_Ammo::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABR_PickUp_Ammo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
