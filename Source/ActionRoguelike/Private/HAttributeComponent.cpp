// Fill out your copyright notice in the Description page of Project Settings.


#include "HAttributeComponent.h"

UHAttributeComponent::UHAttributeComponent()
{
	Health = 100.f;
}

bool UHAttributeComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;

	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);

	return true;

}
