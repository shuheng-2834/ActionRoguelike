// Fill out your copyright notice in the Description page of Project Settings.


#include "A_MagicProjectile.h"

// Sets default values
AA_MagicProjectile::AA_MagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*
	 * 设置碰撞类型，或者使用在引擎中设置的预设配置类型，二者选其中一种
	 */
	//// 设置自身的碰撞类型为世界动态
	//SphereComp->SetCollisionObjectType(ECC_WorldDynamic);
	//// 设置所有的通道碰撞响应为阻塞
	//SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	//// 针对世界动态设置碰撞响应为重叠
	//SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	// 设置碰撞的响应类型为自定义的碰撞通道Projectile

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
	// 打印位置
}

