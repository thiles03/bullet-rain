#include "BR_CharacterStats_Player.h"

// Constructor
UBR_CharacterStats_Player::UBR_CharacterStats_Player()
{
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UBR_CharacterStats_Player::BeginPlay()
{
	Super::BeginPlay();

	
}


// Called every frame
void UBR_CharacterStats_Player::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

