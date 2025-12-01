#include "EnemyCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

AEnemyCharacter::AEnemyCharacter()
{
    GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GetCapsuleComponent()->SetNotifyRigidBodyCollision(true);
    GetCapsuleComponent()->SetGenerateOverlapEvents(true);

    GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AEnemyCharacter::OnEnemyHit);
}


void AEnemyCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);
    // por si quieres hacer algo más aquí luego
}

void AEnemyCharacter::OnEnemyHit(
    UPrimitiveComponent* HitComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    FVector NormalImpulse,
    const FHitResult& Hit)
{
    if (!OtherActor) return;

    UE_LOG(LogTemp, Warning, TEXT("💥 Enemy HIT detectado"));

    if (ACharacter* Player = Cast<ACharacter>(OtherActor))
    {
        FVector PushDir = Player->GetActorLocation() - GetActorLocation();
        PushDir.Z = 0;
        PushDir.Normalize();

        FVector PushForce = PushDir * 1500.0f;

        Player->LaunchCharacter(PushForce, true, true);
    }
}
