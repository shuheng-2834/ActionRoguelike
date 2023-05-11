// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HBaseProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS(Abstract)
class ACTIONROGUELIKE_API AHBaseProjectile : public AActor
{
	GENERATED_BODY()

public:

	// Sets default values for this actor's properties
	AHBaseProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
		UParticleSystem* ImpactVFX;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Components")
		USphereComponent* SphereComp;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UProjectileMovementComponent* MovementComp;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UParticleSystemComponent* EffectComp;

	UFUNCTION()
		virtual void OnActorHit(UPrimitiveComponent* HitComponent,AActor* OtherActor,UPrimitiveComponent* OtherCom,FVector NormalImpulse,const FHitResult& Hit);

	UFUNCTION()
		virtual  void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bBFromSweep, const FHitResult& SweepResult);

	// BlueprintNativeEvent 在c++中进行基础实现，然后可以在蓝图中扩展
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void Explode();

	virtual void PostInitializeComponents() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
