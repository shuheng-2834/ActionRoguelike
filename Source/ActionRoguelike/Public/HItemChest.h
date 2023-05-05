// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GamePlayInterface.h"
#include "GameFramework/Actor.h"
#include "HItemChest.generated.h"

UCLASS()
class ACTIONROGUELIKE_API AHItemChest : public AActor, public IGamePlayInterface
{
	GENERATED_BODY()
	
public:	
	AHItemChest();

	UPROPERTY(EditAnywhere)
	float TargetPitch;

	void Interact_Implementation(APawn* InstigatorPawn);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* LidMesh;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
