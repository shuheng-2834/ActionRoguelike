// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HBaseProjectile.h"
#include "HDashProjecile.generated.h"

UCLASS()
class ACTIONROGUELIKE_API AHDashProjecile : public AHBaseProjectile

{
	GENERATED_BODY()
	
public:	
	AHDashProjecile();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
		float TeleportDelay;
	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
		float DetonateDelay;

	FTimerHandle TimerHandle_DelayedDetonate;

	// 扩展父类的方法，
	virtual void Explode_Implementation() override;

	void TeleportInstigator();

	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
