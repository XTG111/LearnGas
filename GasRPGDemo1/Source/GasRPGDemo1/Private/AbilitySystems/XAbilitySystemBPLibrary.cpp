// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystems/XAbilitySystemBPLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerStates/XPlayerState.h"
#include "UI/HUD/XHUD.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "UI/WidgetController/XAttributeMenuWidgetController.h"

UOverlayWidgetController* UXAbilitySystemBPLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	if(PC)
	{
		if(AXHUD* XHUD = Cast<AXHUD>(PC->GetHUD()))
		{
			AXPlayerState* XPlayerState = PC->GetPlayerState<AXPlayerState>();
			UAbilitySystemComponent* ASC = XPlayerState->GetAbilitySystemComponent();
			UAttributeSet* AS = XPlayerState->GetAttributeSet();
			FWidgetControllerParams WidgetControllerParams(PC,XPlayerState,ASC,AS);
			return XHUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}

UXAttributeMenuWidgetController* UXAbilitySystemBPLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	if(PC)
	{
		if(AXHUD* XHUD = Cast<AXHUD>(PC->GetHUD()))
		{
			AXPlayerState* XPlayerState = PC->GetPlayerState<AXPlayerState>();
			UAbilitySystemComponent* ASC = XPlayerState->GetAbilitySystemComponent();
			UAttributeSet* AS = XPlayerState->GetAttributeSet();
			FWidgetControllerParams WidgetControllerParams(PC,XPlayerState,ASC,AS);
			return XHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}
