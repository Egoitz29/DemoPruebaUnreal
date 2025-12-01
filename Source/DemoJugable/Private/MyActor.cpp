#include "MyActor.h"
#include "Components/StaticMeshComponent.h"

AMyActor::AMyActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
}
