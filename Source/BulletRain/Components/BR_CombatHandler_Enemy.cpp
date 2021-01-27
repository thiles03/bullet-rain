#include "BR_CombatHandler_Enemy.h"
#include "BulletRain/Characters/BR_CharacterPlayer.h"
#include "Kismet/GameplayStatics.h"

// Constructor
UBR_CombatHandler_Enemy::UBR_CombatHandler_Enemy()
{
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts
void UBR_CombatHandler_Enemy::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<ABR_CharacterPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

// Called every frame
void UBR_CombatHandler_Enemy::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// If player is within range then attack
	if(FVector::Dist(GetOwner()->GetActorLocation(), Player->GetActorLocation()) <= (AttackRange + 100.f))
	{
		Attack();
	}
	else
	{
		IsAttacking = false;
	}
}

// Return true is enemy is attacking
bool UBR_CombatHandler_Enemy::GetIsAttacking() const
{
	return IsAttacking;
}

// Set IsAttacking
void UBR_CombatHandler_Enemy::SetIsAttacking(bool Attacking) 
{
	IsAttacking = Attacking;
}
// Attack the player
void UBR_CombatHandler_Enemy::Attack() 
{
	if(IsAttacking == true) return;
	// Do damage
	// Spawn grunt sound
	// Spawn impact sound
	// Spawn vfx
	IsAttacking = true;
}
