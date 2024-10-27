// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystems/XAttributeSet.h"
#include "Net/UnrealNetwork.h"

UXAttributeSet::UXAttributeSet()
{
	InitHealth(100.0f);
	InitMaxHealth(100.0f);;
	InitMana(50.0f);
	InitMaxMana(50.0f);
}

void UXAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UXAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UXAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UXAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UXAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

void UXAttributeSet::OnRep_Health(const FGameplayAttributeData& oldhealth) const
{
	//Show Change to the ability System
	GAMEPLAYATTRIBUTE_REPNOTIFY(UXAttributeSet, Health, oldhealth);
}

void UXAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& oldmaxhealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UXAttributeSet, MaxHealth, oldmaxhealth);
}

void UXAttributeSet::OnRep_Mana(const FGameplayAttributeData& oldmana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UXAttributeSet, Mana, oldmana);
}

void UXAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& oldmaxmana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UXAttributeSet, MaxMana, oldmaxmana);
}
