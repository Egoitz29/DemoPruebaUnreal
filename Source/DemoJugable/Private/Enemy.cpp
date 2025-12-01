#include "Enemy.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyAIController.h"

AEnemy::AEnemy()
{
    PrimaryActorTick.bCanEverTick = true;

    PushTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("PushTrigger"));
    PushTrigger->SetupAttachment(RootComponent);
    PushTrigger->SetSphereRadius(180.f);

    PushTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    PushTrigger->SetCollisionResponseToAllChannels(ECR_Ignore);
    PushTrigger->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    PushTrigger->SetGenerateOverlapEvents(true);

    AIControllerClass = AEnemyAIController::StaticClass();
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

    GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void AEnemy::BeginPlay()
{
    Super::BeginPlay();

    PushTrigger->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnPushTriggerOverlap);
}

void AEnemy::OnPushTriggerOverlap(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    ACharacter* Player = Cast<ACharacter>(OtherActor);

    if (Player)
    {
        FVector PushDirection = (Player->GetActorLocation() - GetActorLocation()).GetSafeNormal();
        float PushStrength = 1500.f;
        FVector LaunchVelocity = PushDirection * PushStrength;
        LaunchVelocity.Z = 200.f;

        Player->LaunchCharacter(LaunchVelocity, true, true);

        UE_LOG(LogTemp, Warning, TEXT("EMPUGE RADIAL! (%s)"),
            *LaunchVelocity.ToString());
    }
}
