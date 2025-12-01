#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

UCLASS()
class DEMOJUGABLE_API AMyPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    // --- Control manual ---
    UFUNCTION(BlueprintCallable, Category = "Control")
    void PossessCharacter(class AMyCharacter* NewCharacter);

    UFUNCTION(BlueprintCallable, Category = "Control")
    void PossessPawn(class AMyPawn* NewPawn);

    // --- Acción de entrada ---
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    class UInputAction* SwitchPawnAction;

protected:
    // --- Configuración de input ---
    virtual void SetupInputComponent() override;

    // --- Alternar control entre Character y Pawn ---
    UFUNCTION()
    void SwitchPawn();
};
