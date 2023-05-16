// Fill out your copyright notice in the Description page of Project Settings.


#include "HDashProjecile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AHDashProjecile::AHDashProjecile()
{
	PrimaryActorTick.bCanEverTick = true;

	TeleportDelay = 0.2f;
	DetonateDelay = 0.2f;

	MovementComp->InitialSpeed = 6000.f;
}

void AHDashProjecile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_DelayedDetonate, this, &AHDashProjecile::Explode, DetonateDelay);
}

// Called every frame
void AHDashProjecile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AHDashProjecile::Explode_Implementation()
{
	// 不调用父类的实现
	// Super::Explode_Implementation();

	GetWorldTimerManager().ClearTimer(TimerHandle_DelayedDetonate);

	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(),GetActorRotation());

	// 禁用粒子系统
	EffectComp->DeactivateSystem();
	// 停止移动
	MovementComp->StopMovementImmediately();
	SetActorEnableCollision(false);

	FTimerHandle TimerHandle_DelayedTeleport;
	GetWorldTimerManager().SetTimer(TimerHandle_DelayedTeleport, this, &AHDashProjecile::TeleportInstigator, TeleportDelay);
}
void AHDashProjecile::TeleportInstigator()
{
	AActor* ActorToTeleport = GetInstigator();
	if(ensure(ActorToTeleport))
	{
		ActorToTeleport->TeleportTo(GetActorLocation(), ActorToTeleport->GetActorRotation(),false,false);
	}
	Destroy();
}

