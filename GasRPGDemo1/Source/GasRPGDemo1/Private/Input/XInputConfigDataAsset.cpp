// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/XInputConfigDataAsset.h"

const UInputAction* UXInputConfigDataAsset::GetInputActionByTag(const FGameplayTag InputTag, bool bIsNotFound) const
{
	for(auto& inputaction : InputActions)
	{
		if(inputaction.InputAction && inputaction.InputTag == InputTag) return inputaction.InputAction;
	}
	return nullptr;
}
