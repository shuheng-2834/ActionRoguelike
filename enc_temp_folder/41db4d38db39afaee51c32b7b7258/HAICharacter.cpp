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

	// �Զ�����AI�����û�������
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AHAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	// Ϊ��֪������¼� 
	PawnSensingComponent->OnSeePawn.AddDynamic(this, &AHAICharacter::OnPawnSeen);
}

void AHAICharacter::OnPawnSeen(APawn* SeenPawn)
{
	AAIController* AIController = Cast<AAIController>(GetController());
	if(AIController)
	{
		// ���úڰ��е�Ŀ�����
		AIController->GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), SeenPawn);

		DrawDebugString(GetWorld(),GetActorLocation(),TEXT("PLAYER SPOTTED"),nullptr,FColor::White);

		// ���úڰ��е�Ŀ��λ��
		AIController->GetBlackboardComponent()->SetValueAsVector(TEXT("MoveToLocation"), SeenPawn->GetActorLocation()); 
	}
}
