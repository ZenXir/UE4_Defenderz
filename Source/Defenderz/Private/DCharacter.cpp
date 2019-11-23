#include "DCharacter.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Components/InputComponent.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "DWeapon.h"

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
	this->TimeBetweenAttacks = 1.f;

	this->LeftHandSocket = "hand_lSocket";
	this->RightHandSocket = "hand_rSocket";
}

void ADCharacter::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters spawnParameters;
	spawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	this->RightHandWep = GetWorld()->SpawnActor<ADWeapon>(WeaponClass, FVector::ZeroVector, FRotator::ZeroRotator, spawnParameters);
	if (RightHandWep)
	{
		this->RightHandWep->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, RightHandSocket);
		this->RightHandWep->SetOwner(this);
	}

	this->LeftHandWep = GetWorld()->SpawnActor<ADWeapon>(WeaponClass, FVector::ZeroVector, FRotator::ZeroRotator, spawnParameters);
	if (LeftHandWep)
	{
		this->LeftHandWep->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, LeftHandSocket);
		this->LeftHandWep->SetOwner(this);
	}
}

void ADCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ADCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &ADCharacter::AddControllerYawInput);

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

	ComboAttackCounter = 0;
}

void ADCharacter::Attack()
{
	LastAttackTime = GetWorld()->TimeSeconds;

	UE_LOG(LogTemp, Display, TEXT("Attack"));

	if (++ComboAttackCounter > 5)
	{
		ComboAttackCounter = 0;
	}
}
