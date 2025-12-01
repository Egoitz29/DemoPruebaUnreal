#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"

void AEnemyAIController::BeginPlay()
{
    Super::BeginPlay();

    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    if (PatrolPoints.Num() > 0)
    {
        MoveToNextPatrolPoint();
    }
}

void AEnemyAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (!PlayerPawn) return;

    float DistanceToPlayer = FVector::Dist(
        GetPawn()->GetActorLocation(),
        PlayerPawn->GetActorLocation()
    );

    if (DistanceToPlayer < ChaseRadius)
    {
        bIsChasing = true;
        MoveToActor(PlayerPawn, 50.f);
        return;
    }

    if (bIsChasing && DistanceToPlayer > LoseInterestRadius)
    {
        bIsChasing = false;
        MoveToNextPatrolPoint();
        return;
    }

    if (!bIsChasing && PatrolPoints.Num() > 0)
    {
        if (!IsFollowingAPath())
        {
            MoveToNextPatrolPoint();
        }
    }
}

void AEnemyAIController::MoveToNextPatrolPoint()
{
    if (PatrolPoints.Num() == 0) return;

    AActor* NextPoint = PatrolPoints[CurrentPatrolIndex];

    MoveToActor(NextPoint, AcceptableRadius);

    CurrentPatrolIndex++;
    if (CurrentPatrolIndex >= PatrolPoints.Num())
    {
        CurrentPatrolIndex = 0;
    }
}
