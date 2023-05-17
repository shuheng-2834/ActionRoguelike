// Fill out your copyright notice in the Description page of Project Settings.


#include "HBaseProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"



// Sets default values
AHBaseProjectile::AHBaseProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->OnComponentHit.AddDynamic(this, &AHBaseProjectile::OnActorHit);
	RootComponent = SphereComp;

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 8000.f;
	MovementComp->ProjectileGravityScale = 0.f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(RootComponent);

	ShakeInnerRadius = 0.f;
	ShakeOuterRadius = 1500.f;

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
	// ��֤��ǰ����û�б����Ϊ�ȴ�����
	if (ensure(!IsPendingKill()))
	{
		// UGameplayStatics ��һ����̬�࣬�����ṩһЩͨ�õ���Ϸ���ܽӿڣ���������Ч�ȡ������ SpawnEmitterAtLocation ���������ڸ���λ������һ��������Ч�����������ɵ���Ч����
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());

		UGameplayStatics::SpawnSoundAtLocation(this, HitSound, GetActorLocation());

		// ����һ�����������
		UGameplayStatics::PlayWorldCameraShake(this, ImpactShake,GetActorLocation(),ShakeInnerRadius,ShakeOuterRadius);

		Destroy();
	}
}
void AHBaseProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

