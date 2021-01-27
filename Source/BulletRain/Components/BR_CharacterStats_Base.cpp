#include "BR_CharacterStats_Base.h"
#include "GameFramework/Pawn.h"
#include "Math/UnrealMathUtility.h"

//Constructor
UBR_CharacterStats_Base::UBR_CharacterStats_Base()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UBR_CharacterStats_Base::BeginPlay()
{
	Super::BeginPlay();
	CurrentArmour = MaxArmour;
	CurrentHealth = MaxHealth;
}


// Called every frame
void UBR_CharacterStats_Base::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (CurrentHealth == 0 && IsDead == false) Die();
}

//SETTERS
void UBR_CharacterStats_Base::SetMaxArmour(float ArmourValue)
{
	MaxArmour = ArmourValue;
}

void UBR_CharacterStats_Base::UpdateCurrentArmour(float ArmourValue)
{
	CurrentArmour = FMath::Clamp(CurrentArmour + ArmourValue, 0.f, MaxArmour);
}

void UBR_CharacterStats_Base::SetMaxHealth(float HealthValue)
{
	MaxHealth = HealthValue;
}

void UBR_CharacterStats_Base::UpdateCurrentHealth(float HealthValue)
{
	CurrentHealth = FMath::Clamp(CurrentHealth + HealthValue, 0.f, MaxHealth);
}

void UBR_CharacterStats_Base::SetIsDead(bool Dead) 
{
	IsDead = Dead;
}

//GETTERS
float UBR_CharacterStats_Base::GetArmourPercent() const
{
	return CurrentArmour / MaxArmour;
}

float UBR_CharacterStats_Base::GetHealthPercent() const
{
	return CurrentHealth / MaxHealth;
}

bool UBR_CharacterStats_Base::GetIsDead() const
{
	return IsDead;
}

// Take blockable damage to armour and health
void UBR_CharacterStats_Base::TakeDamage(float Damage)
{
	if (Damage <= 0) {return;}
	float RemainingDamage = CurrentArmour - Damage;
	UpdateCurrentArmour(0 - Damage);
	if (RemainingDamage < 0)
	{
		UpdateCurrentHealth(RemainingDamage);
	}
}

// Take blockable damage and unblockable damage
void UBR_CharacterStats_Base::TakeUnblockableDamage(float Damage, float UnblockableDamage)
{
	TakeDamage(Damage);
	CurrentHealth = (FMath::Clamp((CurrentHealth - UnblockableDamage), 0.0f, MaxHealth));
}

void UBR_CharacterStats_Base::Die() 
{
	Cast<APawn>(GetOwner())->DetachFromControllerPendingDestroy();
}