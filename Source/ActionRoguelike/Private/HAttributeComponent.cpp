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

	// ������ֵ������
	Health = FMath::Clamp(Health + Delta, 0.f, HealthMax);

	// ʵ�ʱ仯ֵ
	float ActualDelta = Health - OldHealth;

	OnHealthChanged.Broadcast(nullptr, this, Health, ActualDelta);

	// ����б仯������true,û�б仯����false
	return ActualDelta != 0;

}
