#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

// Forward declaration
class USphereComponent;

UCLASS()
class DEMOJUGABLE_API AEnemy : public ACharacter
{
    GENERATED_BODY()

public:
    AEnemy();

protected:
    virtual void BeginPlay() override;

    // Fuerza del empuje
    UPROPERTY(EditAnywhere, Category = "Empuje")
    float PushForce = 1200.0f;

    // Trigger para detectar al jugador
    UPROPERTY(VisibleAnywhere, Category = "Empuje")
    USphereComponent* PushTrigger;

    // Función del Trigger
    UFUNCTION()
    void OnPushTriggerOverlap(
        UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult
    );
};
