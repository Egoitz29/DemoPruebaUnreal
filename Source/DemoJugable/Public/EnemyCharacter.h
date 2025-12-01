#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class DEMOJUGABLE_API AEnemyCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AEnemyCharacter();

protected:

    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

    // ESTA ES LA FUNCIÓN QUE FALTA — AQUÍ VA
    UFUNCTION()
    void OnEnemyHit(
        UPrimitiveComponent* HitComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        FVector NormalImpulse,
        const FHitResult& Hit
    );
};
