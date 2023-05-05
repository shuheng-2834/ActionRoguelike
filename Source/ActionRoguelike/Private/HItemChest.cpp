// Fill out your copyright notice in the Description page of Project Settings.


#include "HItemChest.h"

// Sets default values
AHItemChest::AHItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;
	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");
	LidMesh->SetupAttachment(BaseMesh);
	TargetPitch = 110.f;
}

void AHItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	LidMesh->SetRelativeRotation(FRotator(TargetPitch, 0.0f, 0.0f));
}

// Called when the game starts or when spawned
void AHItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

