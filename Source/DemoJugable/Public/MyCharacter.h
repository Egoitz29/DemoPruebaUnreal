#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Blueprint/UserWidget.h"
#include "NiagaraSystem.h"            // ⭐ NUEVO
#include "MyCharacter.generated.h"

UCLASS()
class DEMOJUGABLE_API AMyCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AMyCharacter();

protected:
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    virtual void Tick(float DeltaTime) override;

    // --- ENHANCED INPUT ---
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    class UInputMappingContext* DefaultMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    class UInputAction* MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    class UInputAction* LookAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    class UInputAction* JumpAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    class UInputAction* InteractAction;

    // --- INVENTARIO ---
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
    int32 Coins = 0;

    // --- HUD / UI ---
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UUserWidget> HUDWidgetClass;

    UPROPERTY()
    UUserWidget* HUDWidgetInstance = nullptr;

    // --- INTERACCIÓN ---
    bool bCanInteract = false;
    AActor* CurrentInteractable = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
    int32 TotalCoinsRequired = 1;

   



    // --- VFX AL RECOGER MONEDAS ---
    UPROPERTY(EditAnywhere, Category = "VFX")
    UNiagaraSystem* CollectVFX;                 // ⭐ NUEVO

    UFUNCTION()
    void OnOverlapSalida(AActor* Overlapped, AActor* Other);

    // --- FUNCIONES ---
    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
    void Interact();
};
