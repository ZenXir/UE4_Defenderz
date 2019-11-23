#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DWeapon.generated.h"

class UStaticMeshComponent;

UCLASS()
class DEFENDERZ_API ADWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ADWeapon();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UStaticMeshComponent* StaticMeshComponent;

protected:
	virtual void BeginPlay() override;
};
