// Fill out your copyright notice in the Description page of Project Settings.


#include "A_MagicProjectile.h"

// Sets default values
AA_MagicProjectile::AA_MagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*
	 * ������ײ���ͣ�����ʹ�������������õ�Ԥ���������ͣ�����ѡ����һ��
	 */
	//// �����������ײ����Ϊ���綯̬
	//SphereComp->SetCollisionObjectType(ECC_WorldDynamic);
	//// �������е�ͨ����ײ��ӦΪ����
	//SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	//// ������綯̬������ײ��ӦΪ�ص�
	//SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	// ������ײ����Ӧ����Ϊ�Զ������ײͨ��Projectile

}

// Called when the game starts or when spawned
void AA_MagicProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AA_MagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// ��ӡλ��
}

