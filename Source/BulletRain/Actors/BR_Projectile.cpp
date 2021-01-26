#include "BR_Projectile.h"
#include "BulletRain/Characters/BR_CharacterPlayer.h"
#include "BulletRain/Components/BR_CombatHandler_Player.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ABR_Projectile::ABR_Projectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collider"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));

	RootComponent = Collider;
	StaticMesh->SetupAttachment(Collider);
}

// Called when the game starts or when spawned
void ABR_Projectile::BeginPlay()
{
	Super::BeginPlay();
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ABR_Projectile::OnBeginOverlap);
	Damage = Cast<ABR_CharacterPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->CombatHandler->GetAttackDamage();
}

// Called every frame
void ABR_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Return projectile's damage value
float ABR_Projectile::GetDamage() 
{
	return Damage;
}

// On hit event
void ABR_Projectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ABR_CharacterPlayer *Player = Cast<ABR_CharacterPlayer>(OtherActor);
	if(Player) return;
	Destroy();
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, SweepResult.Location, (GetActorForwardVector().Rotation())*-1, FVector(-.4f));
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, SweepResult.Location, 2.f);
}