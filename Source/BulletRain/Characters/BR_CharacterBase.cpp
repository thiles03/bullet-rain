#include "BR_CharacterBase.h"
#include "Components/CapsuleComponent.h"
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
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABR_CharacterBase::OnBeginOverlap);
	GetCharacterMovement()->MaxWalkSpeed = MaxSpeed;
}

// Called every frame
void ABR_CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABR_CharacterBase::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// On overlap event
void ABR_CharacterBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	
}

// Set max walk speed
void ABR_CharacterBase::SetSpeed(float Speed) 
{
	GetCharacterMovement()->MaxWalkSpeed = Speed;
}

