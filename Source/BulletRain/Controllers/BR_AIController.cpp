#include "BR_AIController.h"
#include "AI/Navigation/NavigationTypes.h"
#include "BulletRain/Characters/BR_CharacterEnemy.h"
#include "NavigationSystem.h"
#include "TimerManager.h"

// Called when the game starts or when spawned
void ABR_AIController::BeginPlay() 
{
    Super::BeginPlay();
    EnemyCharacter = Cast<ABR_CharacterEnemy>(GetCharacter());
    GetWorldTimerManager().SetTimer(PatrolTimer, this, &ABR_AIController::Patrol, PatrolDelay, true);
}

// Called every frame
void ABR_AIController::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);
}

// Move to within a certain range of a location
void ABR_AIController::Patrol()
{
    if (EnemyCharacter->GetIsPlayerVisible() == true) return;
    FNavLocation Result;
    UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
    NavSys->GetRandomReachablePointInRadius(EnemyCharacter->GetActorLocation(), PatrolRadius, Result);
    MoveToLocation(Result.Location, 0.f);
}

// Move to within attack range of location and reset player visibility on completion
void ABR_AIController::MoveToAttack(FVector Location, float Range)
{
    EPathFollowingRequestResult::Type Result = MoveToLocation(Location, Range);

    if (Result == EPathFollowingRequestResult::RequestSuccessful || EPathFollowingRequestResult::Failed)
    {
        EnemyCharacter->SetIsPlayerVisible(false);
    }
}
