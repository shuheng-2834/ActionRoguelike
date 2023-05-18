// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/HAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AHAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BehaviorTree);

	APawn* MyPawn =  UGameplayStatics::GetPlayerPawn(this, 0);
	if(MyPawn)
	{
		GetBlackboardComponent()->SetValueAsVector(TEXT("MoveToLocatin"), MyPawn->GetActorLocation());

		GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), MyPawn);
	}
}
