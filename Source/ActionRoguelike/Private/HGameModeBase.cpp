// Fill out your copyright notice in the Description page of Project Settings.


#include "HGameModeBase.h"

#include "EngineUtils.h"
#include "HAttributeComponent.h"
#include "AI/HAICharacter.h"
#include "EnvironmentQuery/EnvQueryManager.h"

AHGameModeBase::AHGameModeBase()
{
	spawnTimerInterval = 2.f;
}

void AHGameModeBase::StartPlay()
{
	Super::StartPlay();

	// 设置一个定时器，每次调用更新EQS，生成怪物
	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots, this, &AHGameModeBase::SpawnBotTimerElapsed, spawnTimerInterval, true);
}

void AHGameModeBase::SpawnBotTimerElapsed()
{
	// 生成怪物
	UE_LOG(LogTemp, Warning, TEXT("SpawnBotTimerElapsed"));

	UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnBotQuery, this, EEnvQueryRunMode::RandomBest5Pct, nullptr);
	if (ensure(QueryInstance))
	{
		QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &AHGameModeBase::OnQueryCompleted);
	}
}

void AHGameModeBase::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance,
	EEnvQueryStatus::Type QueryStatus)
{
	if (QueryStatus != EEnvQueryStatus::Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("spawn bot query failed!"))
			return;
	}

	int32 NrOfAliveBots = 0;
	for (TActorIterator<AHAICharacter> It(GetWorld()); It; ++It)
	{
		AHAICharacter* bot = *It;
		UHAttributeComponent* AttributeComponent = Cast<UHAttributeComponent>(bot->GetComponentByClass(UHAttributeComponent::StaticClass()));
		if (AttributeComponent && AttributeComponent->IsAlive())
		{
			++NrOfAliveBots;
		}
	}

	float MaxBotCount = 10; // 最大怪物数量

	if (NrOfAliveBots >= MaxBotCount)
	{
		return;
	}

	if (DifficultyCurve)
	{
		MaxBotCount = DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
	}

	TArray<FVector>  Locations = QueryInstance->GetResultsAsLocations();

	if (Locations.IsValidIndex(0))
	{
		GetWorld()->SpawnActor<AActor>(MinionClass, Locations[0], FRotator::ZeroRotator);
	}
}