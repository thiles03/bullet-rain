#include "BR_CharacterStats_Enemy.h"

// Constructor
UBR_CharacterStats_Enemy::UBR_CharacterStats_Enemy()
{
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UBR_CharacterStats_Enemy::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void UBR_CharacterStats_Enemy::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UBR_CharacterStats_Enemy::Die()
{
	Super::Die();
	GetOwner()->Destroy();
}
