// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystems/XAbilitySystemComponent.h"

void UXAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UXAbilitySystemComponent::EffectApplied);
}

void UXAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                                             const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer); // get all ASSET tags in the effect
	EffecAssetTags.Broadcast(TagContainer);
}
