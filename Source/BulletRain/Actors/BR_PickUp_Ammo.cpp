#include "BR_PickUp_Ammo.h"
#include "BulletRain/Characters/BR_CharacterPlayer.h"
#include "BulletRain/Components/BR_CombatHandler_Player.h"
#include "Kismet/GameplayStatics.h"

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

void ABR_PickUp_Ammo::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) 
{
	Super::OnBeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	Player = Cast<ABR_CharacterPlayer>(OtherActor);
	if (!Player) return;
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), PickupSound, GetOwner()->GetActorLocation());
	Player->CombatHandler->SetCurrentCarriedAmmo(AmmoValue);
	Destroy();		
}
