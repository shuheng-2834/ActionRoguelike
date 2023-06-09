// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "HBTTaskNode_RandgeAttack.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API UHBTTaskNode_RandgeAttack : public UBTTaskNode
{
	GENERATED_BODY()

		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere,Category = "AI")
	TSubclassOf<AActor> ProjectileClass;
};
