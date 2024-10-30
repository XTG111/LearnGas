// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

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
		AbilitySytemComponent->GetGameplayAttributeValueChangeDelegate(
			XAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);

		AbilitySytemComponent->GetGameplayAttributeValueChangeDelegate(
			XAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);

		AbilitySytemComponent->GetGameplayAttributeValueChangeDelegate(
			XAttributeSet->GetManaAttribute()).AddUObject(this,&UOverlayWidgetController::ManaChanged);

		AbilitySytemComponent->GetGameplayAttributeValueChangeDelegate(
			XAttributeSet->GetMaxManaAttribute()).AddUObject(this,&UOverlayWidgetController::MaxManaChanged);
	}
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
