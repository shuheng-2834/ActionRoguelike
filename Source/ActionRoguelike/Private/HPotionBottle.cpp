// Fill out your copyright notice in the Description page of Project Settings.


#include "HPotionBottle.h"

#include "HAttributeComponent.h"

// Sets default values
AHPotionBottle::AHPotionBottle()
{
	PrimaryActorTick.bCanEverTick = true;

	BottleMesh = CreateDefaultSubobject<UStaticMeshComponent>("BottleMesh");
	RootComponent = BottleMesh;

	HealAmount = 10.f;
	TimeShow = 10.f;
}

void AHPotionBottle::Interact_Implementation(APawn* InstigatorPawn)
{
	AActor* Player = InstigatorPawn->GetInstigator();
	UHAttributeComponent* AttributeComponent = Cast<UHAttributeComponent>(Player->GetComponentByClass(UHAttributeComponent::StaticClass()));
	if (ensure(AttributeComponent))
	{
		if (!AttributeComponent->IsFullHealth())
		{
			AttributeComponent->ApplyHealthChange(HealAmount);
			DisableBottle();
		}
	}
}

void AHPotionBottle::DisableBottle()
{
	BottleMesh->SetVisibility(false);
	BottleMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetWorldTimerManager().SetTimer(Handle, this, &AHPotionBottle::EnableBottle, TimeShow, false);
}

void AHPotionBottle::EnableBottle()
{
	BottleMesh->SetVisibility(true);
	BottleMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

// Called when the game starts or when spawned
void AHPotionBottle::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AHPotionBottle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

