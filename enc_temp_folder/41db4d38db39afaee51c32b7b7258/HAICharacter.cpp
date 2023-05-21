// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/HAICharacter.h"

#include "AIController.h"
#include "DrawDebugHelpers.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
AHAICharacter::AHAICharacter()
{
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>("SensingComponent");

	// 自动控制AI，放置或者生成
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AHAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	// 为感知组件绑定事件 
	PawnSensingComponent->OnSeePawn.AddDynamic(this, &AHAICharacter::OnPawnSeen);
}

void AHAICharacter::OnPawnSeen(APawn* SeenPawn)
{
	AAIController* AIController = Cast<AAIController>(GetController());
	if(AIController)
	{
		// 设置黑板中的目标对象
		AIController->GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), SeenPawn);

		DrawDebugString(GetWorld(),GetActorLocation(),TEXT("PLAYER SPOTTED"),nullptr,FColor::White);

		// 设置黑板中的目标位置
		AIController->GetBlackboardComponent()->SetValueAsVector(TEXT("MoveToLocation"), SeenPawn->GetActorLocation()); 
	}
}
