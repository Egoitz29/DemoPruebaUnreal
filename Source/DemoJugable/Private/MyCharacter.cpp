#include "MyCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "NiagaraFunctionLibrary.h"       // ⭐ NUEVO

AMyCharacter::AMyCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AMyCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
    {
        if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
        {
            if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
                ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
            {
                Subsystem->AddMappingContext(DefaultMappingContext, 0);
            }
        }

        // --- HUD ---
        if (HUDWidgetClass)
        {
            HUDWidgetInstance = CreateWidget<UUserWidget>(PlayerController, HUDWidgetClass);

            if (HUDWidgetInstance)
            {
                HUDWidgetInstance->AddToViewport();

                if (UTextBlock* CoinsText =
                    Cast<UTextBlock>(HUDWidgetInstance->GetWidgetFromName(TEXT("CoinsText"))))
                {
                    CoinsText->SetText(FText::FromString(TEXT("MONEDAS: 0")));
                }
            }
        }
    }
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyCharacter::Look);

        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

        EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AMyCharacter::Interact);
    }
}

void AMyCharacter::Move(const FInputActionValue& Value)
{
    FVector2D MovementVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        FRotator Rotation = Controller->GetControlRotation();
        FRotator YawRotation(0, Rotation.Yaw, 0);

        FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        AddMovementInput(ForwardDirection, MovementVector.X);
        AddMovementInput(RightDirection, MovementVector.Y);
    }
}

void AMyCharacter::Look(const FInputActionValue& Value)
{
    FVector2D LookAxisVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        AddControllerYawInput(LookAxisVector.X);
        AddControllerPitchInput(LookAxisVector.Y);
    }
}

void AMyCharacter::Interact()
{
    if (!bCanInteract || !CurrentInteractable) return;

    if (CurrentInteractable->ActorHasTag("Moneda"))
    {
        // Guardamos localización antes de destruir
        FVector VFXLocation = CurrentInteractable->GetActorLocation();
        VFXLocation.Z += 150.f;    // ⭐ SUBE EL EFECTO


        // Spawnear el efecto visual (si está asignado)
        if (CollectVFX)
        {
            UNiagaraFunctionLibrary::SpawnSystemAtLocation(
                GetWorld(),
                CollectVFX,
                VFXLocation,
                FRotator::ZeroRotator,
                FVector(1.f)
            );
        }

        // Sumar moneda
        Coins++;

        // Destruir moneda
        CurrentInteractable->Destroy();
        CurrentInteractable = nullptr;
        bCanInteract = false;

        // UI
        if (HUDWidgetInstance)
        {
            if (UTextBlock* InteractText =
                Cast<UTextBlock>(HUDWidgetInstance->GetWidgetFromName(TEXT("InteractText"))))
            {
                InteractText->SetVisibility(ESlateVisibility::Hidden);
            }

            if (UTextBlock* CoinsText =
                Cast<UTextBlock>(HUDWidgetInstance->GetWidgetFromName(TEXT("CoinsText"))))
            {
                CoinsText->SetText(FText::FromString(FString::Printf(TEXT("MONEDAS: %d"), Coins)));
            }
        }
    }
}

void AMyCharacter::OnOverlapSalida(AActor* Overlapped, AActor* Other)
{
    if (Other->ActorHasTag("Salida"))
    {
        if (Coins >= TotalCoinsRequired)
        {
            // Ganas
            UE_LOG(LogTemp, Warning, TEXT("¡HAS GANADO EL JUEGO!"));

            // Aquí puedes cargar otro nivel, mostrar UI especial, etc.
            UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()));
        }
        else
        {
            int32 Faltan = TotalCoinsRequired - Coins;
            UE_LOG(LogTemp, Warning, TEXT("FALTAN %d MONEDAS"), Faltan);
        }
    }
}


void AMyCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FVector Start = GetActorLocation();
    FVector ForwardVector = GetActorForwardVector();
    FVector End = Start + (ForwardVector * 200.f);

    FHitResult Hit;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);

    GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params);

    if (GetActorLocation().Z < -3000.f)
    {
        UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()));
    }

    if (Hit.GetActor() && Hit.GetActor()->ActorHasTag("Moneda"))
    {
        bCanInteract = true;
        CurrentInteractable = Hit.GetActor();

        if (HUDWidgetInstance)
        {
            if (UTextBlock* InteractText =
                Cast<UTextBlock>(HUDWidgetInstance->GetWidgetFromName(TEXT("InteractText"))))
            {
                InteractText->SetVisibility(ESlateVisibility::Visible);
            }
        }
    }
    else
    {
        bCanInteract = false;
        CurrentInteractable = nullptr;

        if (HUDWidgetInstance)
        {
            if (UTextBlock* InteractText =
                Cast<UTextBlock>(HUDWidgetInstance->GetWidgetFromName(TEXT("InteractText"))))
            {
                InteractText->SetVisibility(ESlateVisibility::Hidden);
            }
        }
    }
}
