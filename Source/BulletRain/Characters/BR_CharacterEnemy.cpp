#include "BR_CharacterEnemy.h"
#include "BulletRain/Actors/BR_Projectile.h"
#include "BulletRain/Components/BR_CharacterStats_Enemy.h"
#include "Perception/PawnSensingComponent.h"

// Constructor
ABR_CharacterEnemy::ABR_CharacterEnemy()
{
    PrimaryActorTick.bCanEverTick = true; // Set this character to call Tick() every frame.

    PawnSensor = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Pawn Sensing"));
    PawnSensor->SensingInterval = .25f; // 4 times per second
    PawnSensor->SetPeripheralVisionAngle(45.f);
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

    PawnSensor->OnSeePawn.AddDynamic(this, &ABR_CharacterEnemy::OnSeePawn);
}

// On overlap event
void ABR_CharacterEnemy::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    Super::OnHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
    class ABR_Projectile *Projectile = Cast<ABR_Projectile>(OtherActor);
    if (Projectile)
    {
        this->FindComponentByClass<UBR_CharacterStats_Enemy>()->TakeDamage(Projectile->GetDamage());
    }
}

void ABR_CharacterEnemy::OnSeePawn(APawn *OtherPawn) 
{
    UE_LOG(LogTemp, Warning, (TEXT("Seen")));
}