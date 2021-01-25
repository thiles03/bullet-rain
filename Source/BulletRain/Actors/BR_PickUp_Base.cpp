#include "BR_PickUp_Base.h"
#include "BulletRain/Characters/BR_CharacterPlayer.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Constructor
ABR_PickUp_Base::ABR_PickUp_Base()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = CapsuleCollider;
	StaticMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABR_PickUp_Base::BeginPlay()
{
	Super::BeginPlay();
	CapsuleCollider->OnComponentBeginOverlap.AddDynamic(this, &ABR_PickUp_Base::OnBeginOverlap);
}

// Called every frame
void ABR_PickUp_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Overlap event
void ABR_PickUp_Base::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) 
{
	Player = Cast<ABR_CharacterPlayer>(OtherActor);
}

