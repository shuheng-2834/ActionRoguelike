// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "A_MagicProjectile.generated.h"

UCLASS()
class ACTIONROGUELIKE_API AA_MagicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AA_MagicProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComp;
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* MovementComp;
	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* EffectComp;
};