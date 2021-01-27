#include "BR_CharacterStats_Enemy.h"
#include "BulletRain/Controllers/BR_PlayerController.h"
#include "BulletRain/GameModes/BR_GameMode_Base.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

// Constructor
UBR_CharacterStats_Enemy::UBR_CharacterStats_Enemy()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UBR_CharacterStats_Enemy::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<ABR_PlayerController>(GetWorld()->GetFirstPlayerController());
}

// Called every frame
void UBR_CharacterStats_Enemy::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UBR_CharacterStats_Enemy::TakeDamage(float Damage) 
{
	Super::TakeDamage(Damage);
	PlayerController->CreateHitMarker();
}

void UBR_CharacterStats_Enemy::TakeUnblockableDamage(float Damage, float UnblockableDamage) 
{
	Super::TakeUnblockableDamage(Damage, UnblockableDamage);
	PlayerController->CreateHitMarker();
}


void UBR_CharacterStats_Enemy::Die()
{
	Super::Die();
	IsDead = true;
	// Destroy timer
	GetOwner()->Destroy();
	Cast<ABR_GameMode_Base>(GetWorld()->GetAuthGameMode())->SetKillCount(1);
}
