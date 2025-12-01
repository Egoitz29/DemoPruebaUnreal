#include "MyPlayerController.h"
#include "MyCharacter.h"
#include "MyPawn.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"

void AMyPlayerController::PossessCharacter(AMyCharacter* NewCharacter)
{
    if (NewCharacter)
    {
        Possess(NewCharacter);
        UE_LOG(LogTemp, Warning, TEXT("Controlando Character"));
    }
}

void AMyPlayerController::PossessPawn(AMyPawn* NewPawn)
{
    if (NewPawn)
    {
        Possess(NewPawn);
        UE_LOG(LogTemp, Warning, TEXT("Controlando Pawn"));
    }
}

void AMyPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent);
    if (EnhancedInput && SwitchPawnAction)
    {
        EnhancedInput->BindAction(SwitchPawnAction, ETriggerEvent::Started, this, &AMyPlayerController::SwitchPawn);
    }
}

void AMyPlayerController::SwitchPawn()
{
    if (!GetWorld()) return;

    TArray<AActor*> Pawns;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyPawn::StaticClass(), Pawns);

    if (Pawns.Num() > 0)
    {
        AMyPawn* TargetPawn = Cast<AMyPawn>(Pawns[0]);
        if (TargetPawn)
        {
            Possess(TargetPawn);
            UE_LOG(LogTemp, Warning, TEXT("🔄 Cambiado a Pawn correctamente"));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("❌ El Pawn no es válido"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("❌ No hay Pawns en la escena"));
    }
}
