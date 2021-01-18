#include "BR_CombatHandler_Player.h"

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
void UBR_CombatHandler_Player::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

