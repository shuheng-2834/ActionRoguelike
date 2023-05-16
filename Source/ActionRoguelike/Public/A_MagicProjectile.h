// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HBaseProjectile.h"
#include "A_MagicProjectile.generated.h"

UCLASS()
class ACTIONROGUELIKE_API AA_MagicProjectile : public AHBaseProjectile
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AA_MagicProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UFUNCTION()
		virtual  void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bBFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		float DamageAmount;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
