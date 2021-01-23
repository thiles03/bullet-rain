#include "BR_PickUp_Base.h"
#include "Components/CapsuleComponent.h"

// Constructor
ABR_PickUp_Base::ABR_PickUp_Base()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABR_PickUp_Base::BeginPlay()
{
	Super::BeginPlay();
	CapsuleCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = CapsuleCollider;
}

// Called every frame
void ABR_PickUp_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
