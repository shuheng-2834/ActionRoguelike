// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/HBTService_CheckAttackRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UHBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// 检测攻击范围
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if (ensure(BlackboardComponent))
	{
		AActor* TargetActor = Cast<AActor>(BlackboardComponent->GetValueAsObject("TargetActor"));

		if (TargetActor)
		{
			AAIController* MyController = OwnerComp.GetAIOwner();
			if (ensure(MyController))
			{
				APawn* AIPawn = MyController->GetPawn();
				if (ensure(AIPawn))
				{
					float Distance = FVector::Distance(AIPawn->GetActorLocation(), TargetActor->GetActorLocation());
					bool bwithinRange = Distance < 2000.0f;

					bool bHasLOS = false;

					if (bwithinRange)
					{
						// 判断是否在视线内
						bHasLOS = MyController->LineOfSightTo(TargetActor);
					}

					// 设置值，是否在攻击范围之内
					BlackboardComponent->SetValueAsBool(AttackRangeKey.SelectedKeyName, (bwithinRange && bHasLOS));
				}
			}
		}
	}
}
