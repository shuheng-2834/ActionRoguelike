// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HTargetDummyActor.generated.h"

class UHAttributeComponent;

UCLASS()
class ACTIONROGUELIKE_API AHTargetDummyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AHTargetDummyActor();

protected:
	UPROPERTY(VisibleAnywhere)
		UHAttributeComponent* AttributeComponents;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComponent;

public:	
	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UHAttributeComponent* OwningComp, float NewHealth, float Delta);
};
