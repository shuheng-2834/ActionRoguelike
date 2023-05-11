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
	// EditAnywhere - ��Bp�༭����ÿ��ʵ���ļ����н��б༭��
	// VisibleAnywhere - �ڱ༭���ͼ������ǡ�ֻ�����ģ����������
	// EditDefaultsOnly - ����ÿ��ʵ���ı���������Bp�༭���б༭
	// VisibleDefaultsOnly - �����ġ�ֻ�������ʣ�����Bp�༭���У���������
	// EditInstanceOnly - ������༭ʵ�������磬�������ڼ�����ʱ��
	// BlueprintReadOnly - ����ͼ�ű�����ֻ���ģ���Ӱ�조��ϸ��Ϣ����壩
	// BlueprintReadWrite - ����ͼ�о��ж�д����Ȩ��
	// category = ��������ϸ������ͼ�����Ĳ˵�����ʾ��

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
	float Health;

public:
	UFUNCTION(BlueprintCallable,Category = "Attributes")
	bool ApplyHealthChange(float Delat);
};
