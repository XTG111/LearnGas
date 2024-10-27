// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "XPlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class GASRPGDEMO1_API UXPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:

	//������ͼ��ʼ������
	virtual void NativeInitializeAnimation() override;

	//����Event Tick����
	virtual void NativeUpdateAnimation(float DeltaTime) override;

private:

	//����˽�б�����Ҫ�ܹ�����ͼ�ɼ��������meta=(AllowPrivateAccess="true")
	UPROPERTY(BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	class AXPlayerCharacter* XPlayerCharacter;
	UPROPERTY(BlueprintReadOnly, Category = MoveMent, meta = (AllowPrivateAccess = "true"))
	float GroundSpeed;
	UPROPERTY(BlueprintReadOnly, Category = MoveMent, meta = (AllowPrivateAccess = "true"))
	bool bIsAccelerating;
	UPROPERTY(BlueprintReadOnly, Category = MoveControl, meta = (AllowPrivateAccess = "true"))
	float Direction;
	UPROPERTY(BlueprintReadOnly, Category = IsInAir, meta = (AllowPrivateAccess = "true"))
	bool bIsInAir;
	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bShouldMove;

	
};