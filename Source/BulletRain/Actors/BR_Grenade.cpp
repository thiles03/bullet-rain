#include "BR_Grenade.h"
#include "BulletRain/Characters/BR_CharacterEnemy.h"
#include "BulletRain/Components/BR_CharacterStats_Enemy.h"
#include "Components/SphereComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"

// Constructor
ABR_Grenade::ABR_Grenade()
{
	PrimaryActorTick.bCanEverTick = true;
	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collider"));
	BlastRadius = CreateDefaultSubobject<USphereComponent>(TEXT("Blast Radius"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = Collider;
	StaticMesh->SetupAttachment(Collider);
	BlastRadius->SetupAttachment(Collider);
	BlastRadius->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BlastRadius->SetSphereRadius(5000.f);
}

// Called when the game starts or when spawned
void ABR_Grenade::BeginPlay()
{
	Super::BeginPlay();
	FVector PlayerForwardVector = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorForwardVector();
	StaticMesh->AddImpulse(PlayerForwardVector * ThrowForce);
	GetWorldTimerManager().SetTimer(DestroyTimer, this, &ABR_Grenade::DestroyActor, Fuse, false);
}

// Called every frame
void ABR_Grenade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Handle dealing damage
void ABR_Grenade::DestroyActor() 
{
	// Effects
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation(), FRotator(0.f) , FVector(10.f));
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplosionSound, GetActorLocation());
	//Damage
	ABR_CharacterEnemy* AnEnemy; 
	TArray<AActor*> OverlappedEnemies;
	BlastRadius->GetOverlappingActors(OverlappedEnemies, ABR_CharacterEnemy::StaticClass());
	for (AActor* Enemy : OverlappedEnemies)
	{
		AnEnemy = Cast<ABR_CharacterEnemy>(Enemy);
		AnEnemy->CharacterStats->TakeDamage(Damage);
		FVector BlastDirection = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Enemy->GetActorLocation()).Vector();
		AnEnemy->GetMesh()->AddImpulse(BlastDirection * BlastForce);
	}
	Destroy();
}