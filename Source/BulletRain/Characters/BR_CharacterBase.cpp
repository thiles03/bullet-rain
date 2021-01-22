#include "BR_CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

// Constructor
ABR_CharacterBase::ABR_CharacterBase()
{
	PrimaryActorTick.bCanEverTick = true; // Set this character to call Tick() every frame.
}

// Called when the game starts or when spawned
void ABR_CharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	GetCharacterMovement()->MaxWalkSpeed = MaxSpeed;
}

// Called every frame
void ABR_CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABR_CharacterBase::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABR_CharacterBase::SetSpeed(float Speed) 
{
	GetCharacterMovement()->MaxWalkSpeed = Speed;
}

