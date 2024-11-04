// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "XAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffecAssetTags, const FGameplayTagContainer& /* Asset Tags */)

/**
 * 
 */
UCLASS()
class GASRPGDEMO1_API UXAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	//when called this function the actor info set success
	//then can bind delegate in this function
	void AbilityActorInfoSet();

	FEffecAssetTags EffecAssetTags;
protected:
	//call back when effect apply -- AbilitySystemComponent.h/FOnGameplayEffectAppliedDelegate
	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle);
};
