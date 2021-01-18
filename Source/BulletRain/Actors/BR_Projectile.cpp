#include "BR_Projectile.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
ABR_Projectile::ABR_Projectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Projectile = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile"));
	CapsuleCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));

	RootComponent = Projectile;
	CapsuleCollider->SetupAttachment(RootComponent);
	StaticMesh->SetupAttachment(CapsuleCollider);
}

// Called when the game starts or when spawned
void ABR_Projectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABR_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}