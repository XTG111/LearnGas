// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/XPlayerAnimInstance.h"

#include "KismetAnimationLibrary.h"
#include "Characters/XPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UXPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	XPlayerCharacter = Cast<AXPlayerCharacter>(TryGetPawnOwner());

}

void UXPlayerAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (XPlayerCharacter == nullptr)
	{
		XPlayerCharacter = Cast<AXPlayerCharacter>(TryGetPawnOwner());
	}

	if (XPlayerCharacter == nullptr)
	{
		return;
	}

	FVector Velocity = XPlayerCharacter->GetVelocity();
	Velocity.Z = 0.0f;
	GroundSpeed = Velocity.Size();
	bShouldMove = GroundSpeed > 3.0f ? true : false;
	Direction = UKismetAnimationLibrary::CalculateDirection(XPlayerCharacter->GetVelocity(), XPlayerCharacter->GetActorRotation());
	//是否在加速
	bIsAccelerating = XPlayerCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.0f ? true : false;
	bIsInAir = XPlayerCharacter->GetCharacterMovement()->IsFalling();
}
