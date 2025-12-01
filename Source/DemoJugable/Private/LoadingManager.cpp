#include "LoadingManager.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"

ALoadingManager::ALoadingManager()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ALoadingManager::BeginPlay()
{
    Super::BeginPlay();

    // Mostrar el widget
    if (LoadingWidgetClass)
    {
        UUserWidget* Widget = CreateWidget(GetWorld(), LoadingWidgetClass);
        if (Widget)
        {
            Widget->AddToViewport();
        }
    }

    // Pequeño delay para cambiar de nivel
    FTimerHandle TimerHandle;
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ALoadingManager::OnLevelLoaded, 0.1f, false);
}

void ALoadingManager::OnLevelLoaded()
{
    UGameplayStatics::OpenLevel(this, "Lvl_ThirdPerson");
}


