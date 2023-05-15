// Fill out your copyright notice in the Description page of Project Settings.


#include "HBaseProjectile.h"

#include "HAttributeComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

void AHBaseProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bBFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		UHAttributeComponent* AttributeCom = Cast<UHAttributeComponent>(OtherActor->GetComponentByClass(UHAttributeComponent::StaticClass()));
		if(AttributeCom)
		{
			AttributeCom->ApplyHealthChange(-20.f);
			Destroy();
		}
	}
}

// Sets default values
AHBaseProjectile::AHBaseProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->OnComponentHit.AddDynamic(this, &AHBaseProjectile::OnActorHit);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AHBaseProjectile::OnActorOverlap);
	RootComponent = SphereComp;

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 8000.f;
	MovementComp->ProjectileGravityScale = 0.f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AHBaseProjectile::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AHBaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHBaseProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherCom,
	FVector NormalImpulse, const FHitResult& Hit)
{
	Explode();
}

void AHBaseProjectile::Explode_Implementation()
{
	// 保证当前对象没有被标记为等待销毁
	if (ensure(!IsPendingKill()))
	{
		// UGameplayStatics 是一个静态类，用于提供一些通用的游戏功能接口，如生成特效等。这里的 SpawnEmitterAtLocation 函数用于在给定位置生成一个粒子特效，并返回生成的特效对象。
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());
		Destroy();
	}
}
void AHBaseProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

