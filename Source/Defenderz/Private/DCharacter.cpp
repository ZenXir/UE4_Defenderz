#include "DCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Components/BoxComponent.h"

ADCharacter::ADCharacter()
{
	this->SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	this->SpringArmComponent->bUsePawnControlRotation = false;
	this->SpringArmComponent->SetRelativeRotation(FRotator(-30.f, 0.f, 0.f));
	this->SpringArmComponent->TargetArmLength = 750.f;
	this->SpringArmComponent->SetupAttachment(RootComponent);

	this->CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	this->CameraComponent->SetupAttachment(SpringArmComponent);

	//this->AttackCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Attack Collider"));
	//this->AttackCollider->SetupAttachment(RootComponent);

	this->ComboAttackCounter = 0;
	this->bAttacking = false;

	this->LastAttackTime = 0.f;
	this->TimeBetweenAttacks = .5f;
}

void ADCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ADCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ADCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &ADCharacter::AddControllerYawInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ADCharacter::OnJump);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ADCharacter::StartAttacking);
	PlayerInputComponent->BindAction("Attack", IE_Released, this, &ADCharacter::StopAttacking);
}

void ADCharacter::MoveForward(float delta)
{
	AddMovementInput(CameraComponent->GetForwardVector(), delta);
}

void ADCharacter::MoveRight(float delta)
{
	AddMovementInput(CameraComponent->GetRightVector(), delta);
}

void ADCharacter::OnJump()
{
	Jump();
}

void ADCharacter::StartAttacking()
{
	if (bAttacking) return;

	bAttacking = true;

	float delay = FMath::Max(LastAttackTime + TimeBetweenAttacks - GetWorld()->TimeSeconds, 0.f);
	GetWorldTimerManager().SetTimer(TimerHandle_Attack, this, &ADCharacter::Attack, TimeBetweenAttacks, true, delay);
}

void ADCharacter::StopAttacking()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_Attack);

	bAttacking = false;
}

void ADCharacter::Attack()
{
	LastAttackTime = GetWorld()->TimeSeconds;

	UE_LOG(LogTemp, Display, TEXT("Attack"));

	UAnimInstance* attackAnimationInstance = GetMesh()->GetAnimInstance();
	UAnimMontage* attackAnimation = ComboAttackAnimations[ComboAttackCounter];

	if (attackAnimationInstance && attackAnimation)
	{
		attackAnimationInstance->Montage_Play(attackAnimation);

		if (++ComboAttackCounter >= ComboAttackAnimations.Num())
		{
			ComboAttackCounter = 0;
		}
	}
}
