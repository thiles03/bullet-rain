#include "BR_CharacterStats_Player.h"
#include "BulletRain/Controllers/BR_PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

// Constructor
UBR_CharacterStats_Player::UBR_CharacterStats_Player()
{
	PrimaryComponentTick.bCanEverTick = true;
	RemainingBulletTime = MaxBulletTime;
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

	// Health regen
	if (CurrentHealth > 0 && CanRegenHealth)
	{
		UpdateCurrentHealth((GetWorld()->GetDeltaSeconds()) * HealthRegenRate);
	}
	// Bullet time regen
	if (CanRegenBulletTime)
	{
		UpdateRemainingBulletTime((GetWorld()->GetDeltaSeconds()) * BulletTimeRegenRate);
	}
	if (!CanRegenBulletTime)
	{
		UpdateRemainingBulletTime((GetWorld()->GetDeltaSeconds()) * -2.f);
	}
	if (RemainingBulletTime == 0)
	{
		BulletTime();
	}
}

// Get remaining bullet time as percentage
float UBR_CharacterStats_Player::GetRemainingBulletTime() const
{
	return RemainingBulletTime / MaxBulletTime;
}

// Return true is bullet time is active
bool UBR_CharacterStats_Player::GetBulletTimeActive() const
{
	return IsBulletTimeActive;
}

// Set the max duration for player bullet time
void UBR_CharacterStats_Player::SetMaxBulletTime(float TimeValue) 
{
	MaxBulletTime = TimeValue;
}

// Increase or decrease bullet time remaining
void UBR_CharacterStats_Player::UpdateRemainingBulletTime(float TimeValue) 
{
	RemainingBulletTime = FMath::Clamp(RemainingBulletTime + TimeValue, 0.f, MaxBulletTime);
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

void UBR_CharacterStats_Player::BulletTime() 
{
	if (IsBulletTimeActive)
	{
		IsBulletTimeActive = false;
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
		CanRegenBulletTime = true;
	}
	else
	{
		PlayerController->CreateSloMoVignette();
		IsBulletTimeActive = true;
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), .5f);
		CanRegenBulletTime = false;
	}
}

// Enable health regeneration
void UBR_CharacterStats_Player::EnableRegen() 
{
	CanRegenHealth = true;
}

void UBR_CharacterStats_Player::Die()
{
	
}

// Suspend health regen and spawn damage vignette
void UBR_CharacterStats_Player::Damaged() 
{
	CanRegenHealth = false;
	GetOwner()->GetWorldTimerManager().SetTimer(RegenResetTimer, this, &UBR_CharacterStats_Player::EnableRegen, RegenDelay, false);
	PlayerController->CreateDamageVignette();
}
