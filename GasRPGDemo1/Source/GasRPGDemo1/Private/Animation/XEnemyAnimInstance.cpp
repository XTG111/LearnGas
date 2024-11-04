// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/XEnemyAnimInstance.h"

#include "KismetAnimationLibrary.h"
#include "Characters/XEnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UXEnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	XEnemyCharacter = Cast<AXEnemyCharacter>(TryGetPawnOwner());
}

void UXEnemyAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (XEnemyCharacter == nullptr)
	{
		XEnemyCharacter = Cast<AXEnemyCharacter>(TryGetPawnOwner());
	}

	if (XEnemyCharacter == nullptr)
	{
		return;
	}

	FVector Velocity = XEnemyCharacter->GetVelocity();
	Velocity.Z = 0.0f;
	GroundSpeed = Velocity.Size();
	Direction = UKismetAnimationLibrary::CalculateDirection(XEnemyCharacter->GetVelocity(), XEnemyCharacter->GetActorRotation());
	//是否在加速
	bIsAccelerating = XEnemyCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.0f ? true : false;
	bIsInAir = XEnemyCharacter->GetCharacterMovement()->IsFalling();
}
