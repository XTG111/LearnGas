// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "XInputConfigDataAsset.h"
#include "XEnhancedInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class GASRPGDEMO1_API UXEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<typename UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindInputActionFunction(UXInputConfigDataAsset* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc);
};

template <typename UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UXEnhancedInputComponent::BindInputActionFunction(UXInputConfigDataAsset* InputConfig, UserClass* Object,
	PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	check(InputConfig);
	for(auto& action : InputConfig->InputActions)
	{
		if(PressedFunc)
		{
			BindAction(action.InputAction,ETriggerEvent::Started,Object,PressedFunc,action.InputTag);
		}
		if(PressedFunc)
		{
			BindAction(action.InputAction,ETriggerEvent::Completed,Object,ReleasedFunc,action.InputTag);
		}
		if(PressedFunc)
		{
			BindAction(action.InputAction,ETriggerEvent::Triggered,Object,HeldFunc,action.InputTag);
		}
	}
}
