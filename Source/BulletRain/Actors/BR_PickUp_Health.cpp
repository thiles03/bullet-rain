#include "BR_PickUp_Health.h"
#include "BulletRain/Characters/BR_CharacterPlayer.h"
#include "BulletRain/Components/BR_CharacterStats_Player.h"

// Constructor
ABR_PickUp_Health::ABR_PickUp_Health()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABR_PickUp_Health::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABR_PickUp_Health::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABR_PickUp_Health::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) 
{
	Super::OnBeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (!Player) return;
	Player->PlayerStats->UpdateCurrentHealth(HealthValue);
	Destroy();		
}
