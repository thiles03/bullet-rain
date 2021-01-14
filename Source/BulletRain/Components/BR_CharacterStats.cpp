#include "BR_CharacterStats.h"

//Constructor
UBR_CharacterStats::UBR_CharacterStats()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UBR_CharacterStats::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UBR_CharacterStats::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

//SETTERS
void UBR_CharacterStats::SetArmour(float ArmourValue) 
{
	Armour = ArmourValue;
}

void UBR_CharacterStats::SetHealth(float HealthValue) 
{
	Health = HealthValue;
}

//GETTERS
float UBR_CharacterStats::GetArmour() const
{
	return Armour;
}

float UBR_CharacterStats::GetHealth() const
{
	return Health;
}

