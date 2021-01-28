#include "BR_CharacterEnemy.h"
#include "BR_CharacterPlayer.h"
#include "BulletRain/Actors/BR_Projectile.h"
#include "BulletRain/Components/BR_CharacterStats_Enemy.h"
#include "BulletRain/Components/BR_CombatHandler_Enemy.h"
#include "BulletRain/Controllers/BR_AIController.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/PawnSensingComponent.h"

// Constructor
ABR_CharacterEnemy::ABR_CharacterEnemy()
{
    PrimaryActorTick.bCanEverTick = true; // Set this character to call Tick() every frame.

	CharacterCombatHandler = CreateDefaultSubobject<UBR_CombatHandler_Enemy>(TEXT("Combat Handler"));
	CharacterStats = CreateDefaultSubobject<UBR_CharacterStats_Enemy>(TEXT("Character Stats"));
    PawnSensor = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Pawn Sensing"));
    PawnSensor->SensingInterval = .2f;
    PawnSensor->SetPeripheralVisionAngle(55.f);
}

// Called every frame
void ABR_CharacterEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

bool ABR_CharacterEnemy::GetIsPlayerVisible() 
{
    return IsPlayerVisible;
}

void ABR_CharacterEnemy::SetIsPlayerVisible(bool IsVisible) 
{
    IsPlayerVisible = IsVisible;
}

// Called when the game starts or when spawned
void ABR_CharacterEnemy::BeginPlay()
{
    Super::BeginPlay();
    AIController = Cast<ABR_AIController>(GetController());
    PawnSensor->OnSeePawn.AddDynamic(this, &ABR_CharacterEnemy::OnSeePawn);
}

// On overlap event
void ABR_CharacterEnemy::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
    Super::OnBeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
    class ABR_Projectile *Projectile = Cast<ABR_Projectile>(OtherActor);
    if (Projectile)
    {
        this->CharacterStats->TakeDamage(Projectile->GetDamage());
        LookAtTarget(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)->GetActorLocation());
    }
}

// Called when another pawn enters viewcone
void ABR_CharacterEnemy::OnSeePawn(APawn *OtherPawn) 
{
    ABR_CharacterPlayer *Player = Cast<ABR_CharacterPlayer>(OtherPawn);
    if (Player)
    {
        IsPlayerVisible = true;
        AIController->MoveToAttack(Player->GetActorLocation(), CharacterCombatHandler->GetAttackRange());
    }
}

void ABR_CharacterEnemy::LookAtTarget(FVector LookAtTarget)
{
	// Update character rotation to face LookAtTarget
	FVector LookAtTargetClean = FVector(LookAtTarget.X, LookAtTarget.Y, GetActorLocation().Z);
	FVector StartLocation = GetActorLocation();
	FRotator CharacterRoatation = FVector(LookAtTargetClean - StartLocation).Rotation();
	this->SetActorRotation(CharacterRoatation);
}