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

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		float DamageAmount;
	UPROPERTY(VisibleAnywhere, Category = "Sound")
		UAudioComponent* AudioComp;

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
