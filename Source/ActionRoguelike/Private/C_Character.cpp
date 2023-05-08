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
	// 使用控制器旋转，
	SpringArm->bUsePawnControlRotation = true;
	// 将弹簧臂组件附加到根组件里面
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	// 将摄像机组件附加到弹簧臂组件里面
	Camera->SetupAttachment(SpringArm);

	InteractionComponent = CreateDefaultSubobject<UHInteractionComponent>("InteractionComp");

	// 设置角色的移动方式
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
	// 使用控制器旋转，但是不要旋转俯仰和滚动
	FRotator ControlRotator = GetControlRotation();
	ControlRotator.Pitch = 0.0f;
	ControlRotator.Roll = 0.0f;
	// 添加移动输入
	AddMovementInput(ControlRotator.Vector(), X);
}

void AC_Character::MoveRight(float X)
{
	// 使用控制器旋转，但是不要旋转俯仰和滚动
	FRotator ControlRotator = GetControlRotation();
	ControlRotator.Pitch = 0.0f;
	ControlRotator.Roll = 0.0f;

	// 获取右向量
	FVector RightVector = FRotationMatrix(ControlRotator).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVector, X);
}

void AC_Character::PrimaryAttack()
{
	// 播放动画
	PlayAnimMontage(AttackMontage);

	GetWorldTimerManager().SetTimer(TimerHandle, this, &AC_Character::PrimaryAttack_TimeElapsed, 0.2f);
	// 角色死亡,清空定时器
	// GetWorldTimerManager().ClearTimer(TimerHandle);
}
void AC_Character::PrimaryAttack_TimeElapsed()
{
	Attack(ProjectileClass);
}

void AC_Character::UltimateAttack()
{
	// 播放动画
	PlayAnimMontage(AttackMontage);

	GetWorldTimerManager().SetTimer(TimerHandle, this, &AC_Character::UltimateAttack_TimeElapsed, 0.2f);
	// 角色死亡,清空定时器
	// GetWorldTimerManager().ClearTimer(TimerHandle);
}
void AC_Character::UltimateAttack_TimeElapsed()
{
	Attack(UltimateProjectileClass);
}

void AC_Character::Attack(TSubclassOf<AActor> Projectile)
{
	// 获取骨架，再获取骨架上炮口的位置
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

	//FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);

	//FActorSpawnParameters SpawnParams;
	//// 设置碰撞处理方式为始终生成
	//SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	//// 设置生成的子弹的对象为当前角色
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

	// 忽视自身
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	bool bHit = GetWorld()->SweepSingleByObjectType(HitResult, Start, End, FQuat::Identity, ObjectTypes, Shape, Params);
	// 绘制Debug追踪线
	FColor LineColor = bHit ? FColor::Red : FColor::Green;
	DrawDebugLine(GetWorld(), Start, End, LineColor, false, 1.f, 0, 1.f);

	// 设置生成参数
	FActorSpawnParameters SpawnParams;
	// 设置碰撞处理方式为始终生成
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	// 设置生成的子弹的对象为当前角色
	SpawnParams.Instigator = this;
	// 配置生成子弹位置及其旋转信息
	FTransform SpawnTM;
	FRotator ProjRotator;

	// 如果击中，则通过击中位置来计算旋转，如果没有击中，则通过射线终点来计算旋转
	if (bHit)
	{
		// 获取被击中的物体的位置
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

