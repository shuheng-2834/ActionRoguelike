// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Character.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AC_Character::AC_Character()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	// 将弹簧臂组件附加到根组件里面
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	// 将摄像机组件附加到弹簧臂组件里面
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void AC_Character::BeginPlay()
{
	Super::BeginPlay();

}

void AC_Character::MoveForward(float X)
{
	UE_LOG(LogTemp, Warning, TEXT("MoveForward: %f"), X);
	// 添加移动输入
	AddMovementInput(GetActorForwardVector(), X);
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
	PlayerInputComponent->BindAxis("Turn", this, &AC_Character::AddControllerYawInput);
}

