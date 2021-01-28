#include "BR_AIController.h"
#include "AI/Navigation/NavigationTypes.h"
#include "BulletRain/Characters/BR_CharacterEnemy.h"
#include "NavigationSystem.h"
#include "TimerManager.h"

// Called when the game starts or when spawned
void ABR_AIController::BeginPlay() 
{
    Super::BeginPlay();
}

// Called every frame
void ABR_AIController::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);
}

// Move to within a certain range of a location
void ABR_AIController::Patrol()
{
    EnemyCharacter = Cast<ABR_CharacterEnemy>(GetCharacter());
    if (!EnemyCharacter || EnemyCharacter->GetIsPlayerVisible() == true) return;
    FNavLocation Result;
    UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
    NavSys->GetRandomReachablePointInRadius(EnemyCharacter->GetActorLocation(), PatrolRadius, Result);
    MoveToLocation(Result.Location, 0.f);
}

// Move to within attack range of location
void ABR_AIController::MoveToAttack(FVector Location, float Range)
{
    MoveToLocation(Location, Range);
    GetWorldTimerManager().SetTimer(VisibilityTimer, this, &ABR_AIController::ResetPlayerVisible, ResetVisibiltyDelay, true);
}

// Reset player visibility
void ABR_AIController::ResetPlayerVisible()
{
    if (EnemyCharacter) EnemyCharacter->SetIsPlayerVisible(false);
}

// Start repeating patrol timer
void ABR_AIController::StartPatrolling() 
{
    EnemyCharacter = Cast<ABR_CharacterEnemy>(GetCharacter());
    EnemyCharacter->SetIsPatrolling(true);
    GetWorldTimerManager().SetTimer(PatrolTimer, this, &ABR_AIController::Patrol, PatrolDelay, true);
}
