// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HInteractionComponent.generated.h"

/**
 * 该类是一个组件类，用于处理交互的逻辑
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUELIKE_API UHInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	/*
	 * 主要交互方法
	 */
	void PrimaryInteract();

public:	
	// Sets default values for this component's properties
	UHInteractionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
