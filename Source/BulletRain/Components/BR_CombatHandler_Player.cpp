#include "BR_CombatHandler_Player.h"
#include "BulletRain/Actors/BR_Projectile.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/Character.h"

// Constructor
UBR_CombatHandler_Player::UBR_CombatHandler_Player()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UBR_CombatHandler_Player::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UBR_CombatHandler_Player::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UBR_CombatHandler_Player::FireLeft()
{	
	if (ProjectileClass)
	{
		const USkeletalMeshSocket *Muzzle = Cast<ACharacter>(GetOwner())->GetMesh()->GetSocketByName("Muzzle_02");
		FVector SpawnLocation = Muzzle->GetSocketLocalTransform().GetLocation();
		FRotator SpawnRotation = Muzzle->GetSocketLocalTransform().GetRotation().Rotator();
		ABR_Projectile *ProjectileTemp = GetWorld()->SpawnActor<ABR_Projectile>(ProjectileClass, SpawnLocation, SpawnRotation);
	}
}

void UBR_CombatHandler_Player::FireRight()
{
		if (ProjectileClass)
	{
		const USkeletalMeshSocket *Muzzle = Cast<ACharacter>(GetOwner())->GetMesh()->GetSocketByName("Muzzle_01");
		FVector SpawnLocation = Muzzle->GetSocketLocalTransform().GetLocation();
		FRotator SpawnRotation = Muzzle->GetSocketLocalTransform().GetRotation().Rotator();
		ABR_Projectile *ProjectileTemp = GetWorld()->SpawnActor<ABR_Projectile>(ProjectileClass, SpawnLocation, SpawnRotation);
	}
}