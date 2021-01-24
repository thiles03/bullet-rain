#include "BR_CharacterEnemy.h"
#include "BulletRain/Actors/BR_Projectile.h"

// Constructor
ABR_CharacterEnemy::ABR_CharacterEnemy()
{
    PrimaryActorTick.bCanEverTick = true; // Set this character to call Tick() every frame.
}

// Called every frame
void ABR_CharacterEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called when the game starts or when spawned
void ABR_CharacterEnemy::BeginPlay()
{
    Super::BeginPlay();
}

// On overlap event
void ABR_CharacterEnemy::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    Super::OnHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
    class ABR_Projectile *Projectile = Cast<ABR_Projectile>(OtherActor);
    if (Projectile) UE_LOG(LogTemp, Error, TEXT("Projectile Hit!"));
    UE_LOG(LogTemp, Error, TEXT("Child Hit!"))
}