// Fill out your copyright notice in the Description page of Project Settings.


#include "AExplosiveBarrel.h"

#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
AAExplosiveBarrel::AAExplosiveBarrel()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;
	MeshComp->SetSimulatePhysics(true);
	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	RadialForceComp->SetupAttachment(RootComponent);
	RadialForceComp->ImpulseStrength = 1000000.f;
	RadialForceComp->Radius = 600.f;

}

void AAExplosiveBarrel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	RadialForceComp->FireImpulse();
}

// Called when the game starts or when spawned
void AAExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	// 
	MeshComp->OnComponentHit.AddDynamic(this, &AAExplosiveBarrel::OnHit);
}

// Called every frame
void AAExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

