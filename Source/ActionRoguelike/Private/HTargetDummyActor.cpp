// Fill out your copyright notice in the Description page of Project Settings.


#include "HTargetDummyActor.h"

#include "HAttributeComponent.h"

// Sets default values
AHTargetDummyActor::AHTargetDummyActor()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

	AttributeComponents = CreateDefaultSubobject<UHAttributeComponent>(TEXT("AttributeComponents"));

	AttributeComponents->OnHealthChanged.AddDynamic(this, &AHTargetDummyActor::OnHealthChanged);
}

void AHTargetDummyActor::OnHealthChanged(AActor* InstigatorActor, UHAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if(Delta < 0.0f)
	{
		MeshComponent->SetScalarParameterValueOnMaterials(TEXT("TimeToHit"), GetWorld()->TimeSeconds);
	}

}


