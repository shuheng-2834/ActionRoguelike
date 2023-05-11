// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HAttributeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUELIKE_API UHAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHAttributeComponent();

protected:
	// EditAnywhere - 在Bp编辑器和每个实例的级别中进行编辑。
	// VisibleAnywhere - 在编辑器和级别中是“只读”的（用于组件）
	// EditDefaultsOnly - 隐藏每个实例的变量，仅在Bp编辑器中编辑
	// VisibleDefaultsOnly - 变量的“只读”访问，仅在Bp编辑器中（不常见）
	// EditInstanceOnly - 仅允许编辑实例（例如，当放置在级别中时）
	// BlueprintReadOnly - 在蓝图脚本中是只读的（不影响“详细信息”面板）
	// BlueprintReadWrite - 在蓝图中具有读写访问权限
	// category = 仅用于详细面板和蓝图上下文菜单的显示。

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
	float Health;

public:
	UFUNCTION(BlueprintCallable,Category = "Attributes")
	bool ApplyHealthChange(float Delat);
};
