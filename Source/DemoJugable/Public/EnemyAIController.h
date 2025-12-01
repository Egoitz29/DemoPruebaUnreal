#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

UCLASS()
class DEMOJUGABLE_API AEnemyAIController : public AAIController
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

    // <<<--- NUEVO: lista de waypoints
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    TArray<AActor*> PatrolPoints;


protected:
    APawn* PlayerPawn;

    int32 CurrentPatrolIndex = 0;
    float AcceptableRadius = 80.f;

    bool bIsChasing = false;
    float ChaseRadius = 600.f;         // empieza a perseguir
    float LoseInterestRadius = 900.f;  // deja de perseguir

    void MoveToNextPatrolPoint();
};
