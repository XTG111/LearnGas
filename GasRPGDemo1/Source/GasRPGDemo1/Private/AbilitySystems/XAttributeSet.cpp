// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystems/XAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "AbilitySystemBlueprintLibrary.h"


UXAttributeSet::UXAttributeSet()
{
}

void UXAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//vital attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UXAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UXAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	//primary attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UXAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UXAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UXAttributeSet, Resilience, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UXAttributeSet, Vigor, COND_None, REPNOTIFY_Always);
	//secondary attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UXAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UXAttributeSet, ArmorPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UXAttributeSet, BlockChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UXAttributeSet, CriticalHitChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UXAttributeSet, CriticalHitDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UXAttributeSet, CriticalHitResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UXAttributeSet, HealthRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UXAttributeSet, ManaRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UXAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
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

	//Real Value Set
	if(Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
	}
	if(Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.0f, GetMaxMana()));
	}
}

void UXAttributeSet::OnRep_Health(const FGameplayAttributeData& oldhealth) const
{
	//Show Change to the ability System
	GAMEPLAYATTRIBUTE_REPNOTIFY(UXAttributeSet, Health, oldhealth);
}

void UXAttributeSet::OnRep_Mana(const FGameplayAttributeData& oldmana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UXAttributeSet, Mana, oldmana);
}

void UXAttributeSet::OnRep_Strength(const FGameplayAttributeData& oldstrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UXAttributeSet, MaxMana, oldstrength);
}

void UXAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& oldintelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UXAttributeSet, MaxMana, oldintelligence);
}

void UXAttributeSet::OnRep_Resilience(const FGameplayAttributeData& oldresilience) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UXAttributeSet, MaxMana, oldresilience);
}

void UXAttributeSet::OnRep_Vigor(const FGameplayAttributeData& oldvigor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UXAttributeSet, MaxMana, oldvigor);
}

#pragma region secondary attributes
void UXAttributeSet::OnRep_Armor(const FGameplayAttributeData& oldarmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UXAttributeSet, MaxMana, oldarmor);
}

void UXAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& oldarmorpenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UXAttributeSet, MaxMana, oldarmorpenetration);
}

void UXAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& oldblockchance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UXAttributeSet, MaxMana, oldblockchance);
}

void UXAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& oldcriticalhitchance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UXAttributeSet, MaxMana, oldcriticalhitchance);
}

void UXAttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& oldcriticalhitdamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UXAttributeSet, MaxMana, oldcriticalhitdamage);
}

void UXAttributeSet::OnRep_CriticalHitResistance(const FGameplayAttributeData& oldcriticalhitresistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UXAttributeSet, MaxMana, oldcriticalhitresistance);
}

void UXAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& oldhealthregeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UXAttributeSet, MaxMana, oldhealthregeneration);
}

void UXAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& oldmanaregeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UXAttributeSet, MaxMana, oldmanaregeneration);
}
void UXAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& oldmaxhealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UXAttributeSet, MaxHealth, oldmaxhealth);
}
void UXAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& oldmaxmana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UXAttributeSet, MaxMana, oldmaxmana);
}
#pragma endregion



