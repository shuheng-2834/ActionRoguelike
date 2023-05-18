// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GamePlayInterface.h"
#include "GameFramework/Actor.h"
#include "HPotionBottle.generated.h"

class UHInteractionComponent;

UCLASS()
class ACTIONROGUELIKE_API AHPotionBottle : public AActor,public IGamePlayInterface
{
	GENERATED_BODY()
	
public:	
	AHPotionBottle();

	void Interact_Implementation(APawn* InstigatorPawn);

	UFUNCTION(BlueprintCallable)
		void DisableBottle();
	UFUNCTION(BlueprintCallable)
		void EnableBottle();
protected:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BottleMesh;

	UPROPERTY(EditAnywhere,Category = "Amount")
	float HealAmount;

	UPROPERTY(EditAnywhere, Category = "Time")
		float TimeShow;
	
	FTimerHandle Handle;

	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
