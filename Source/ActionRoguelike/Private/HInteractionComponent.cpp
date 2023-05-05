// Fill out your copyright notice in the Description page of Project Settings.


#include "HInteractionComponent.h"

#include "DrawDebugHelpers.h"
#include "GamePlayInterface.h"

void UHInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjectTypes;
	ObjectTypes.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldDynamic);
	// ��ȡ���������
	AActor* MyOwner = GetOwner();

	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector End = EyeLocation + EyeRotation.Vector() * 1000.f;

	//FHitResult HitResult;
	//bool bBlockinHit =  GetWorld()->LineTraceSingleByObjectType(HitResult, EyeLocation, End, ObjectTypes);
	//AActor* HitActor = HitResult.GetActor();
	//if (HitActor)
	//{
	//	// �����е�Actor�Ƿ�̳��˿ɽ����ӿ�
	//	if (HitActor->Implements<UGamePlayInterface>())
	//	{
	//		APawn* MyPawn = Cast<APawn>(MyOwner);

	//		IGamePlayInterface::Execute_Interact(HitActor, MyPawn);
	//	}
	//}

	TArray<FHitResult> HitResults;
	FCollisionShape Shape;
	float Radius = 30.f;
	Shape.SetSphere(Radius);

	// ����һ��������ײ�壬����Ƿ��пɽ�����Actor
	bool bBlockinHit = GetWorld()->SweepMultiByObjectType(HitResults, EyeLocation, End, FQuat::Identity, ObjectTypes, Shape);
	FColor LineColor = bBlockinHit ? FColor::Green : FColor::Red;

	for (FHitResult HitResult : HitResults)
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor)
		{
			// �����е�Actor�Ƿ�̳��˿ɽ����ӿ�
			if (HitActor->Implements<UGamePlayInterface>())
			{
				APawn* MyPawn = Cast<APawn>(MyOwner);

				// ���ÿɽ����ӿ�
				IGamePlayInterface::Execute_Interact(HitActor, MyPawn);
				break;
			}
		}
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, Radius, 16, LineColor, false, 1.f, 0, 1.f);

	}

	DrawDebugLine(GetWorld(), EyeLocation, End, LineColor, false, 1.f, 0, 1.f);

}

// Sets default values for this component's properties
UHInteractionComponent::UHInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UHInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

