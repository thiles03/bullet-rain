#include "BR_PickUp_Grenade.h"
#include "BulletRain/Characters/BR_CharacterPlayer.h"
#include "BulletRain/Components/BR_CombatHandler_Player.h"

// Constructor
ABR_PickUp_Grenade::ABR_PickUp_Grenade()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABR_PickUp_Grenade::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABR_PickUp_Grenade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABR_PickUp_Grenade::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) 
{
	Super::OnBeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (!Player) return;
	Player->CombatHandler->SetCurrentGrenades(GrenadeValue);
	Destroy();		
}
