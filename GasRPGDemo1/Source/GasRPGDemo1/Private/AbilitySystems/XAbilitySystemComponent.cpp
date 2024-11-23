// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystems/XAbilitySystemComponent.h"

#include "AbilitySystems/Abilities/XGameplayAbility.h"

void UXAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UXAbilitySystemComponent::ClientEffectApplied);
}

void UXAbilitySystemComponent::AddGameplayAbilities(const TArray<TSubclassOf<UGameplayAbility>> abilities)
{
	for(auto& abilityclass : abilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(abilityclass,1);
		if(UXGameplayAbility* XGA = Cast<UXGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(XGA->StartInputTag);
			GiveAbility(AbilitySpec);//grate the ability
		}
	}
}

void UXAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& tag)
{
	if(!tag.IsValid()) return;
	//Actiate the Ability
	for(auto& abilityspec : GetActivatableAbilities())
	{
		if(abilityspec.DynamicAbilityTags.HasTagExact(tag)) //匹配tag
		{
			AbilitySpecInputPressed(abilityspec);
			if(!abilityspec.IsActive())
			{
				TryActivateAbility(abilityspec.Handle);
			}
		}
	}
}

void UXAbilitySystemComponent::AbilityInputTagRealesed(const FGameplayTag& tag)
{
	if(!tag.IsValid()) return;
	//Actiate the Ability
	for(auto& abilityspec : GetActivatableAbilities())
	{
		if(abilityspec.DynamicAbilityTags.HasTagExact(tag)) //匹配tag
		{
			AbilitySpecInputReleased(abilityspec);
		}
	}
}

void UXAbilitySystemComponent::ClientEffectApplied_Implementation(UAbilitySystemComponent* AbilitySystemComponent,
                                             const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer); // get all ASSET tags in the effect
	EffecAssetTags.Broadcast(TagContainer);
}
