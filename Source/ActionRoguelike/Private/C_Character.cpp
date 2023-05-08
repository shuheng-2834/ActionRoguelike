// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Character.h"

#include "A_MagicProjectile.h"
#include "HInteractionComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
AC_Character::AC_Character()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	// ʹ�ÿ�������ת��
	SpringArm->bUsePawnControlRotation = true;
	// �����ɱ�������ӵ����������
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	// �������������ӵ����ɱ��������
	Camera->SetupAttachment(SpringArm);

	InteractionComponent = CreateDefaultSubobject<UHInteractionComponent>("InteractionComp");

	// ���ý�ɫ���ƶ���ʽ
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void AC_Character::BeginPlay()
{
	Super::BeginPlay();
}

void AC_Character::MoveForward(float X)
{
	// ʹ�ÿ�������ת�����ǲ�Ҫ��ת�����͹���
	FRotator ControlRotator = GetControlRotation();
	ControlRotator.Pitch = 0.0f;
	ControlRotator.Roll = 0.0f;
	// ����ƶ�����
	AddMovementInput(ControlRotator.Vector(), X);
}

void AC_Character::MoveRight(float X)
{
	// ʹ�ÿ�������ת�����ǲ�Ҫ��ת�����͹���
	FRotator ControlRotator = GetControlRotation();
	ControlRotator.Pitch = 0.0f;
	ControlRotator.Roll = 0.0f;

	// ��ȡ������
	FVector RightVector = FRotationMatrix(ControlRotator).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVector, X);
}

void AC_Character::PrimaryAttack()
{
	// ���Ŷ���
	PlayAnimMontage(AttackMontage);

	GetWorldTimerManager().SetTimer(TimerHandle, this, &AC_Character::PrimaryAttack_TimeElapsed, 0.2f);
	// ��ɫ����,��ն�ʱ��
	// GetWorldTimerManager().ClearTimer(TimerHandle);
}
void AC_Character::PrimaryAttack_TimeElapsed()
{
	Attack(ProjectileClass);
}

void AC_Character::UltimateAttack()
{
	// ���Ŷ���
	PlayAnimMontage(AttackMontage);

	GetWorldTimerManager().SetTimer(TimerHandle, this, &AC_Character::UltimateAttack_TimeElapsed, 0.2f);
	// ��ɫ����,��ն�ʱ��
	// GetWorldTimerManager().ClearTimer(TimerHandle);
}
void AC_Character::UltimateAttack_TimeElapsed()
{
	Attack(UltimateProjectileClass);
}

void AC_Character::Attack(TSubclassOf<AActor> Projectile)
{
	// ��ȡ�Ǽܣ��ٻ�ȡ�Ǽ����ڿڵ�λ��
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

	//FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);

	//FActorSpawnParameters SpawnParams;
	//// ������ײ����ʽΪʼ������
	//SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	//// �������ɵ��ӵ��Ķ���Ϊ��ǰ��ɫ
	//SpawnParams.Instigator = this;

	FVector Start = Camera->GetComponentLocation();
	FVector End = Camera->GetComponentRotation().Vector() * 5000.f + Start;

	FHitResult HitResult;
	FCollisionObjectQueryParams ObjectTypes;
	ObjectTypes.AddObjectTypesToQuery(ECC_WorldDynamic);
	ObjectTypes.AddObjectTypesToQuery(ECC_WorldStatic);
	ObjectTypes.AddObjectTypesToQuery(ECC_Pawn);

	FCollisionShape Shape;
	Shape.SetSphere(20.f);

	// ��������
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	bool bHit = GetWorld()->SweepSingleByObjectType(HitResult, Start, End, FQuat::Identity, ObjectTypes, Shape, Params);
	// ����Debug׷����
	FColor LineColor = bHit ? FColor::Red : FColor::Green;
	DrawDebugLine(GetWorld(), Start, End, LineColor, false, 1.f, 0, 1.f);

	// �������ɲ���
	FActorSpawnParameters SpawnParams;
	// ������ײ����ʽΪʼ������
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	// �������ɵ��ӵ��Ķ���Ϊ��ǰ��ɫ
	SpawnParams.Instigator = this;
	// ���������ӵ�λ�ü�����ת��Ϣ
	FTransform SpawnTM;
	FRotator ProjRotator;

	// ������У���ͨ������λ����������ת�����û�л��У���ͨ�������յ���������ת
	if (bHit)
	{
		// ��ȡ�����е������λ��
		ProjRotator = FRotationMatrix::MakeFromX(HitResult.ImpactPoint - HandLocation).Rotator();
	}
	else
	{
		ProjRotator = FRotationMatrix::MakeFromX(End - HandLocation).Rotator();
	}
	SpawnTM = FTransform(ProjRotator, HandLocation);
	GetWorld()->SpawnActor<AActor>(Projectile, SpawnTM, SpawnParams);
}

void AC_Character::PrimaryInteract()
{
	if (InteractionComponent)
	{
		InteractionComponent->PrimaryInteract();
	}
}

// Called every frame
void AC_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AC_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AC_Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AC_Character::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AC_Character::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AC_Character::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AC_Character::Jump);
	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &AC_Character::PrimaryAttack);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &AC_Character::PrimaryInteract);
	PlayerInputComponent->BindAction("UltimateAttack", IE_Pressed, this, &AC_Character::UltimateAttack);
}

