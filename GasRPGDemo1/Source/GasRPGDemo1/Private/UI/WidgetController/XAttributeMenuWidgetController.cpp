// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/XAttributeMenuWidgetController.h"

#include "XGameplayTags.h"
#include "AbilitySystems/XAttributeSet.h"

void UXAttributeMenuWidgetController::BroadCastInitValue()
{
	UXAttributeSet* AS = CastChecked<UXAttributeSet>(AttributeSet);
	check(AttributeInfoData);

	//get the Attribute Info so we can set the value
	//and we can broadCast
	for(auto& pair : AS->TagsToAttributes)
	{
		BoradCastAttributeInfo(pair.Key, pair.Value());
	}
}

void UXAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	UXAttributeSet* AS = CastChecked<UXAttributeSet>(AttributeSet);
	for(auto& pair : AS->TagsToAttributes)
	{
		AbilitySytemComponent->GetGameplayAttributeValueChangeDelegate(pair.Value()).AddLambda(
			[this, pair](const FOnAttributeChangeData& Data)
			{
				BoradCastAttributeInfo(pair.Key, pair.Value());
			}
			);
	}
}

void UXAttributeMenuWidgetController::BoradCastAttributeInfo(const FGameplayTag& GameplayTag,
	const FGameplayAttribute& Attribute)
{
	FXAttributeInfo Info = AttributeInfoData->FindAttributeInfoForTag(GameplayTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	OnAttributeValueChanged.Broadcast(Info);
}
