#include "BR_Projectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SceneComponent.h"

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
	Collider->OnComponentHit.AddDynamic(this, &ABR_Projectile::OnHit);
}

// Called every frame
void ABR_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// On hit event
void ABR_Projectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Destroy();
}