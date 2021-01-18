#include "BR_CombatHandler_Enemy.h"

// Constructor
UBR_CombatHandler_Enemy::UBR_CombatHandler_Enemy()
{
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UBR_CombatHandler_Enemy::BeginPlay()
{
	Super::BeginPlay();

	
}


// Called every frame
void UBR_CombatHandler_Enemy::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

