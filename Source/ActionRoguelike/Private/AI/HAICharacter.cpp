// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/HAICharacter.h"

// Sets default values
AHAICharacter::AHAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


