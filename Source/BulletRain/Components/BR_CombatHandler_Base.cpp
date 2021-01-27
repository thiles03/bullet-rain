#include "BR_CombatHandler_Base.h"

// Constructor
UBR_CombatHandler_Base::UBR_CombatHandler_Base()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UBR_CombatHandler_Base::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UBR_CombatHandler_Base::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

// Get attack damage
float UBR_CombatHandler_Base::GetAttackDamage() const
{
	return AttackDamage;
}

// Get attack speed
float UBR_CombatHandler_Base::GetAttackSpeed() const
{
	return AttackSpeed;
}

// Get attack range
float UBR_CombatHandler_Base::GetAttackRange() const 
{
	return AttackRange;
}

