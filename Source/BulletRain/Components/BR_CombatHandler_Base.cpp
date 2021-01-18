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

