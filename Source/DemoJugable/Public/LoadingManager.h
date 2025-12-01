#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LoadingManager.generated.h"

UCLASS()
class DEMOJUGABLE_API ALoadingManager : public AActor
{
    GENERATED_BODY()

public:
    ALoadingManager();

protected:
    virtual void BeginPlay() override;

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loading")
    TSubclassOf<class UUserWidget> LoadingWidgetClass;

    UFUNCTION()
    void OnLevelLoaded();

    FString LevelToLoad = "Lvl_ThirdPerson";
};
