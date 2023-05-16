// Fill out your copyright notice in the Description page of Project Settings.


#include "HAttributeComponent.h"

UHAttributeComponent::UHAttributeComponent()
{
	HealthMax = 100.f;
	Health = HealthMax;
}

bool UHAttributeComponent::IsAlive() const
{
	return Health > 0.f;
}

bool UHAttributeComponent::IsFullHealth() const
{

	return Health == HealthMax;
}

float UHAttributeComponent::GetHeathMax() const
{
	return HealthMax;
}

bool UHAttributeComponent::ApplyHealthChange(float Delta)
{
	float OldHealth = Health;

	// 将生命值做限制
	Health = FMath::Clamp(Health + Delta, 0.f, HealthMax);

	// 实际变化值
	float ActualDelta = Health - OldHealth;

	OnHealthChanged.Broadcast(nullptr, this, Health, ActualDelta);

	// 如果有变化，返回true,没有变化返回false
	return ActualDelta != 0;

}
