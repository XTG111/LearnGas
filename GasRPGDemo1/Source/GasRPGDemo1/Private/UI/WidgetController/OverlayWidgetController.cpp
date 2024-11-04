// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystems/XAbilitySystemComponent.h"
#include "AbilitySystems/XAttributeSet.h"

void UOverlayWidgetController::BroadCastInitValue()
{
	UXAttributeSet* XAttributeSet = CastChecked<UXAttributeSet>(AttributeSet);
	if (XAttributeSet)
	{
		OnHealthChanged.Broadcast(XAttributeSet->GetHealth());
		OnMaxHealthChanged.Broadcast(XAttributeSet->GetMaxHealth());
		OnManaChanged.Broadcast(XAttributeSet->GetMana());
		OnMaxManaChanged.Broadcast(XAttributeSet->GetMaxMana());
	}
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	UXAttributeSet* XAttributeSet = CastChecked<UXAttributeSet>(AttributeSet);
	if (XAttributeSet)
	{
		AbilitySytemComponent->GetGameplayAttributeValueChangeDelegate(XAttributeSet->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
				{
					OnHealthChanged.Broadcast(Data.NewValue);
				}
		);
		
		AbilitySytemComponent->GetGameplayAttributeValueChangeDelegate(XAttributeSet->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
				{
					OnMaxHealthChanged.Broadcast(Data.NewValue);
				}
		);
		
		AbilitySytemComponent->GetGameplayAttributeValueChangeDelegate(XAttributeSet->GetManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
				{
					OnManaChanged.Broadcast(Data.NewValue);
				}
		);
		
		AbilitySytemComponent->GetGameplayAttributeValueChangeDelegate(XAttributeSet->GetMaxManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
				{
					OnMaxManaChanged.Broadcast(Data.NewValue);
				}
		);
	}
	Cast<UXAbilitySystemComponent>(AbilitySytemComponent)->EffecAssetTags.AddLambda(
		[this](const FGameplayTagContainer& TagContainer)
		{
			for(const FGameplayTag& tag : TagContainer)
			{
				//Find the original tag
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
				//MessageTag = Message
				//if tag = Message.HealthPotion
				//"Message.HealthPotion".MatchesTag("Message") will return True, "Message".MatchesTag("Message.HealthPotion") will return False
				if(tag.MatchesTag(MessageTag))
				{
					//just want the message tag effect show in UI
					
					FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, tag);
					MessageWidgetRowSignature.Broadcast(*Row);
				}
			}
		}
		);
}
