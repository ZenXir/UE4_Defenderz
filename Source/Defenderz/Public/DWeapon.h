#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DWeapon.generated.h"

UCLASS()
class DEFENDERZ_API ADWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ADWeapon();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
};
