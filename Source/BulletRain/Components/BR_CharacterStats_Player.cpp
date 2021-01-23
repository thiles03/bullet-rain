#include "BR_CharacterStats_Player.h"
#include "BulletRain/Controllers/BR_PlayerController.h"
#include "TimerManager.h"

// Constructor
UBR_CharacterStats_Player::UBR_CharacterStats_Player()
{
	PrimaryComponentTick.bCanEverTick = true;
	RemainingBulletTime = MaxBulletTime;
}

// Get remaining bullet time as percentage
float UBR_CharacterStats_Player::GetRemainingBulletTime() const
{
	return RemainingBulletTime / MaxBulletTime;
}

void UBR_CharacterStats_Player::SetMaxBulletTime(float Time) 
{
	MaxBulletTime = Time;
}

// Called when the game starts
void UBR_CharacterStats_Player::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<ABR_PlayerController>(GetWorld()->GetFirstPlayerController());

}

// Called every frame
void UBR_CharacterStats_Player::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Health regen
	if (CurrentHealth > 0 && CanRegen)
	{
		UpdateCurrentHealth((GetWorld()->GetDeltaSeconds()) * HealthRegenRate);
	}
}

// // Take blockable damage to armour and health
void UBR_CharacterStats_Player::TakeDamage(float Damage) 
{
	Super::TakeDamage(Damage);
	Damaged();
}

// Take blockable damage and unblockable damage
void UBR_CharacterStats_Player::TakeUnblockableDamage(float Damage, float UnblockableDamage) 
{
	Super::TakeUnblockableDamage(Damage, UnblockableDamage);
	Damaged();
}

// Enable health regeneration
void UBR_CharacterStats_Player::EnableRegen() 
{
	CanRegen = true;
}

void UBR_CharacterStats_Player::Die()
{
	
}

// Suspend health regen and spawn damage vignette
void UBR_CharacterStats_Player::Damaged() 
{
	CanRegen = false;
	GetOwner()->GetWorldTimerManager().SetTimer(RegenResetTimer, this, &UBR_CharacterStats_Player::EnableRegen, RegenDelay, false);
	PlayerController->CreateDamageVignette();
}
