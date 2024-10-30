// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/XWidgetController.h"

void UXWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCparams)
{
	PlayerController = WCparams.PlayerController;
	PlayerState = WCparams.PlayerState;
	AbilitySytemComponent = WCparams.AbilitySystemComponent;
	AttributeSet = WCparams.AttributeSet;
}

void UXWidgetController::BroadCastInitValue()
{
}

void UXWidgetController::BindCallbacksToDependencies()
{
}
