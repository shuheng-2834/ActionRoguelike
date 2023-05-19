// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HBaseProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;
class UCameraShakeBase;

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
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
		USoundBase* HitSound;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
		TSubclassOf<UCameraShakeBase> ImpactShake;
	UPROPERTY(EditAnywhere,Category = "Camera")
		float ShakeInnerRadius;
	UPROPERTY(EditAnywhere, Category = "Camera")
		float ShakeOuterRadius;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USphereComponent* SphereComp;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UProjectileMovementComponent* MovementComp;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UParticleSystemComponent* EffectComp;


	UFUNCTION(BlueprintCallable)
		virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherCom, FVector NormalImpulse, const FHitResult& Hit);

	// BlueprintNativeEvent 在c++中进行基础实现，然后可以在蓝图中扩展
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void Explode();

	virtual void PostInitializeComponents() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
