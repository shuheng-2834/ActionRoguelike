// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "C_Character.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UHInteractionComponent;

UCLASS()
class ACTIONROGUELIKE_API AC_Character : public ACharacter
{
	GENERATED_BODY()

protected:
	// ָ�����ɵ�����
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;

public:
	// Sets default values for this character's properties
	AC_Character();

protected:

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
	UHInteractionComponent* InteractionComponent;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float X);
	void MoveRight(float X);
	void PrimaryAttack();
	void PrimaryInteract();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
