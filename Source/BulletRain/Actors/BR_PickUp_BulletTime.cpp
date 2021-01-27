#include "BR_PickUp_BulletTime.h"
#include "BulletRain/Characters/BR_CharacterPlayer.h"
#include "BulletRain/Components/BR_CharacterStats_Player.h"

// Constructor
ABR_PickUp_BulletTime::ABR_PickUp_BulletTime()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABR_PickUp_BulletTime::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABR_PickUp_BulletTime::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABR_PickUp_BulletTime::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) 
{
	Super::OnBeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (!Player) return;
	Player->PlayerStats->UpdateRemainingBulletTime(BulletTimeValue);
	Destroy();		
}
