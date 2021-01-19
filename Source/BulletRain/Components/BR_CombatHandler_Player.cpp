#include "BR_CombatHandler_Player.h"
#include "BulletRain/Actors/BR_Projectile.h"
#include "Components/SceneComponent.h"
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

void UBR_CombatHandler_Player::Fire(EPistol Pistol)
{	
	FName Socket = "Muzzle_Left";
	if (Pistol == EPistol::RIGHT)
	{
		Socket = "Muzzle_Right";
	}

	if (!ProjectileClass) {return;}
	FTransform SpawnTransform = Cast<ACharacter>(GetOwner())->GetMesh()->GetSocketTransform(Socket);
	ABR_Projectile *ProjectileTemp = GetWorld()->SpawnActor<ABR_Projectile>(ProjectileClass, SpawnTransform);
}