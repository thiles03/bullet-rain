#include "BR_CharacterStats.h"
#include "Math/UnrealMathUtility.h"

//Constructor
UBR_CharacterStats::UBR_CharacterStats()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UBR_CharacterStats::BeginPlay()
{
	Super::BeginPlay();
	CurrentArmour = MaxArmour;
	CurrentHealth = MaxHealth;
}

// Called every frame
void UBR_CharacterStats::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

//SETTERS
void UBR_CharacterStats::SetMaxArmour(float ArmourValue) 
{
	MaxArmour = ArmourValue;
}

void UBR_CharacterStats::UpdateCurrentArmour(float ArmourValue) 
{
	CurrentArmour = FMath::Clamp(CurrentArmour + ArmourValue, 0.f, MaxArmour);
}

void UBR_CharacterStats::SetMaxHealth(float HealthValue) 
{
	MaxHealth = HealthValue;
}

void UBR_CharacterStats::UpdateCurrentHealth(float HealthValue) 
{
	CurrentHealth = FMath::Clamp(CurrentHealth + HealthValue, 0.f, MaxHealth);
}

//GETTERS
float UBR_CharacterStats::GetArmourPercent() const
{
	return CurrentArmour / MaxArmour;
}

float UBR_CharacterStats::GetHealthPercent() const
{
	return CurrentHealth / MaxHealth;
}

// Take general damage to armour and health
void UBR_CharacterStats::TakeDamage(float Damage) 
{
	if (Damage <= 0) {return;}
	float RemainingDamage = CurrentArmour - Damage;
	UpdateCurrentArmour(0 - Damage);
	if (RemainingDamage < 0)
	{
		UpdateCurrentHealth(RemainingDamage);
	}
}

// Take general damage and unblockable damage
void UBR_CharacterStats::TakeUnblockableDamage(float Damage, float UnblockableDamage) 
{
	TakeDamage(Damage);
	UpdateCurrentHealth(FMath::Clamp((CurrentHealth - UnblockableDamage), 0.0f, MaxHealth));
}

