// Fill out your copyright notice in the Description page of Project Settings.


#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "AbilitySystems/XAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"


UXAttributeSet::UXAttributeSet()
{
	InitHealth(50.0f);
	InitMaxHealth(100.0f);;
	InitMana(20.0f);
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

void UXAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if(Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
	if(Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxMana());
	}
}


void UXAttributeSet::SetFEffectProperties(const struct FGameplayEffectModCallbackData& Data,
	FEffectProperties& EffectProperties) const
{
	//source -- 产生effect的对象 target -- effect的目标对象（该AS的owner）
	//获取source
	EffectProperties.EffectContextHandle = Data.EffectSpec.GetContext(); //effect info
	EffectProperties.SourceASC = EffectProperties.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent(); //source obj ASC
	if(IsValid(EffectProperties.SourceASC) && EffectProperties.SourceASC->AbilityActorInfo.IsValid() && EffectProperties.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		EffectProperties.SourceAvatarActor = EffectProperties.SourceASC->AbilityActorInfo->AvatarActor.Get(); //source actor
		EffectProperties.SourceController = EffectProperties.SourceASC->AbilityActorInfo->PlayerController.Get(); //source controller
		if(EffectProperties.SourceController == nullptr && EffectProperties.SourceController != nullptr)
		{
			if(const APawn* Pawn = Cast<APawn>(EffectProperties.SourceAvatarActor))
			{
				EffectProperties.SourceController = Pawn->GetController(); //another way get controller
			}
		}
		if(EffectProperties.SourceController)
		{
			EffectProperties.SourceCharacter = Cast<ACharacter>(EffectProperties.SourceController->GetPawn()); // cast to character
		}
	}
	//获取target
	if(Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		EffectProperties.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		EffectProperties.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		EffectProperties.TargetCharacter = Cast<ACharacter>(EffectProperties.TargetAvatarActor);
		EffectProperties.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(EffectProperties.TargetAvatarActor);
	}
}

void UXAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	 
	FEffectProperties EffectProperties;
	SetFEffectProperties(Data, EffectProperties);
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


