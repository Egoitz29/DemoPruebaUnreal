#include "MyPawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"

AMyPawn::AMyPawn()
{
    PrimaryActorTick.bCanEverTick = true;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = MeshComponent;

    MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(RootComponent);
}

void AMyPawn::BeginPlay()
{
    Super::BeginPlay();
}

void AMyPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &AMyPawn::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AMyPawn::MoveRight);
    PlayerInputComponent->BindAxis("MoveUp", this, &AMyPawn::MoveUp);
}

void AMyPawn::MoveForward(float Value)
{
    AddMovementInput(GetActorForwardVector(), Value);
}

void AMyPawn::MoveRight(float Value)
{
    AddMovementInput(GetActorRightVector(), Value);
}

void AMyPawn::MoveUp(float Value)
{
    AddMovementInput(GetActorUpVector(), Value);
}
