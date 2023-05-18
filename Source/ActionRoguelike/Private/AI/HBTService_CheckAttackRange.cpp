// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/HBTService_CheckAttackRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UHBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// ��⹥����Χ
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
						// �ж��Ƿ���������
						bHasLOS = MyController->LineOfSightTo(TargetActor);
					}

					// ����ֵ���Ƿ��ڹ�����Χ֮��
					BlackboardComponent->SetValueAsBool(AttackRangeKey.SelectedKeyName, (bwithinRange && bHasLOS));
				}
			}
		}
	}
}
