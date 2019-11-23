#include "DWeapon.h"

#include "Components/StaticMeshComponent.h"

ADWeapon::ADWeapon()
{
	this->StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	this->StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	RootComponent = this->StaticMeshComponent;
}

void ADWeapon::BeginPlay()
{
	Super::BeginPlay();
}
