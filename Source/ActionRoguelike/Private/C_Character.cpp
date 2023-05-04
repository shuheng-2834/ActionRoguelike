// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Character.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AC_Character::AC_Character()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArm->bUsePawnControlRotation = true;
	// 将弹簧臂组件附加到根组件里面
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	// 将摄像机组件附加到弹簧臂组件里面
	Camera->SetupAttachment(SpringArm);

	// 设置朝向运行为真
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
  	FVector RightVector =  FRotationMatrix(ControlRotator).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVector, X);
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
}

  