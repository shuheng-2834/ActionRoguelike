// Fill out your copyright notice in the Description page of Project Settings.


#include "HAttributeComponent.h"

// Sets default values for this component's properties
UHAttributeComponent::UHAttributeComponent()
{
	Health = 100.f;
}

bool UHAttributeComponent::ApplyHealthChange(float Delat)
{
	Health += Delat;
	UE_LOG(LogTemp, Warning, TEXT("Health Changed: %f"), Health);
	return true;

}