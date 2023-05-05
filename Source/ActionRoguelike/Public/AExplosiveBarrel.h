// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AExplosiveBarrel.generated.h"

UCLASS()
class ACTIONROGUELIKE_API AAExplosiveBarrel : public AActor
{
	GENERATED_BODY()

public:
	AAExplosiveBarrel();

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MeshComp;
	UPROPERTY(VisibleAnywhere)
		class URadialForceComponent* RadialForceComp;

protected:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
