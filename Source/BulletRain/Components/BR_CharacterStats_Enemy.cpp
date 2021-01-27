#include "BR_CharacterStats_Enemy.h"
#include "BulletRain/Characters/BR_CharacterEnemy.h"
#include "BulletRain/Controllers/BR_PlayerController.h"
#include "BulletRain/GameModes/BR_GameMode_Base.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"

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

void UBR_CharacterStats_Enemy::TakeExplosiveDamage(FVector ExplosionLocation, FVector BlastForce) 
{
	Die();
	FVector BlastDirection = UKismetMathLibrary::FindLookAtRotation(ExplosionLocation, GetOwner()->GetActorLocation()).Vector();
	Cast<ABR_CharacterEnemy>(GetOwner())->GetMesh()->AddImpulse(BlastDirection * BlastForce);
}

void UBR_CharacterStats_Enemy::Die()
{
	Super::Die();
	IsDead = true;
	ABR_CharacterEnemy* EnemyCharacter = Cast<ABR_CharacterEnemy>(GetOwner());
	EnemyCharacter->GetMesh()->SetSimulatePhysics(true);
	EnemyCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetWorld()->GetTimerManager().SetTimer(DestroyTimer, this, &UBR_CharacterStats_Enemy::DestroyActor, DestroyDelay, false);
	Cast<ABR_GameMode_Base>(GetWorld()->GetAuthGameMode())->SetKillCount(1);
}

void UBR_CharacterStats_Enemy::DestroyActor() 
{
	GetOwner()->Destroy();
}
