#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UBoxComponent;
class ADWeapon;

UCLASS()
class DEFENDERZ_API ADCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ADCharacter();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay")
	TArray<UAnimMontage*> ComboAttackAnimations;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Gameplay")
	int ComboAttackCounter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay")
	UAnimMontage* AttackAnimationMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gameplay")
	bool bAttacking;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gameplay")
	float TimeBetweenAttacks;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gameplay")
	//UBoxComponent* AttackCollider;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay")
	TSubclassOf<ADWeapon> WeaponClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gameplay")
	ADWeapon* RightHandWep;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gameplay")
	ADWeapon* LeftHandWep;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Socket")
	FName RightHandSocket;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Socket")
	FName LeftHandSocket;

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	void MoveForward(float delta);
	void MoveRight(float delta);

	void StartAttacking();
	void StopAttacking();
	void Attack();

private:
	FTimerHandle TimerHandle_Attack;

	float LastAttackTime;
};
