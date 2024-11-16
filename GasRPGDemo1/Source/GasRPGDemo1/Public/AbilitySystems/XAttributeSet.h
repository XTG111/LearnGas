// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "XAttributeSet.generated.h"



#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT(BlueprintType)
struct FEffectProperties
{
	GENERATED_BODY()
	FEffectProperties(){}

	//effect context
	FGameplayEffectContextHandle EffectContextHandle;

	//Source
	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;
	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;
	UPROPERTY()
	AController* SourceController = nullptr;
	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	//Target
	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;
	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;
	UPROPERTY()
	AController* TargetController = nullptr;
	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
};

//typedef TBaseStaticDelegateInstance<FGameplayAttribute(),FDefaultDelegateUserPolicy>::FFuncPtr FAttributeFuncPtr;
template<typename T>
using TStaicFuncPtr = typename TBaseStaticDelegateInstance<T,FDefaultDelegateUserPolicy>::FFuncPtr;

/**
 * 
 */
UCLASS()
class GASRPGDEMO1_API UXAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UXAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//call befor the effect apply
	//so if we clamp the value, and when the effect doing and cause the value beyond the max now the another effect coming
	//the attribute will recaculate by the no clamp value 
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override; //just clamping the attribute value change

	//call after the effect apply and the attribute is already set
	//so we can clamp here for change the real value
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;


	//using TMap to save the Attribute and the GameplayTag So we can use gameplaytag to find attribute and get the value
	//like the XAttributeMenuWidgetController.h
	TMap<FGameplayTag,TStaicFuncPtr<FGameplayAttribute()>> TagsToAttributes;
	
	//begin Attributes
#pragma region primary attribute
	//strength use for increase physical damage
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "Primary Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UXAttributeSet, Strength);
	//intelligence use for increase magical damage
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence, Category = "Primary Attributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UXAttributeSet, Intelligence);
	// resilience use for increases armor and armor penetration
	//** armor reduces damage taken improves block chance
	//** armor penetration ignores percentage of enemy armor, increase crit hit chance
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Resilience, Category = "Primary Attributes")
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(UXAttributeSet, Resilience);
	//vigor use for increases health
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Vigor, Category = "Primary Attributes")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UXAttributeSet, Vigor);
#pragma endregion
	
#pragma region vital attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UXAttributeSet, Health);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UXAttributeSet, Mana);
#pragma endregion

#pragma region secondary attributes
	/***
	 *      Secondary Attributes
	 ***/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category = "Secondary Attributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UXAttributeSet, Armor);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArmorPenetration, Category = "Secondary Attributes")
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UXAttributeSet, ArmorPenetration);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BlockChance, Category = "Secondary Attributes")
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(UXAttributeSet, BlockChance);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitChance, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS(UXAttributeSet, CriticalHitChance);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitDamage, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS(UXAttributeSet, CriticalHitDamage);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitResistance, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitResistance;
	ATTRIBUTE_ACCESSORS(UXAttributeSet, CriticalHitResistance);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegeneration, Category = "Secondary Attributes")
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(UXAttributeSet, HealthRegeneration);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegeneration, Category = "Secondary Attributes")
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(UXAttributeSet, ManaRegeneration);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UXAttributeSet, MaxHealth);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Vital Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UXAttributeSet, MaxMana);
#pragma endregion
	//end Attributes
	

	//begin OnRep Func
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& oldhealth) const;
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& oldmana) const;
	
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& oldstrength) const;
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& oldintelligence) const;
	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& oldresilience) const;
	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& oldvigor) const;

#pragma region secondary attributes function
	/***
	*      Secondary Attributes
	***/
	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& oldarmor) const;
	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& oldarmorpenetration) const;
	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& oldblockchance) const;
	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& oldcriticalhitchance) const;
	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& oldcriticalhitdamage) const;
	UFUNCTION()
	void OnRep_CriticalHitResistance(const FGameplayAttributeData& oldcriticalhitresistance) const;
	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& oldhealthregeneration) const;
	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& oldmanaregeneration) const;
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& oldmaxhealth) const;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& oldmaxmana) const;
#pragma endregion
	//end OnRep Func

private:
	void SetFEffectProperties(const struct FGameplayEffectModCallbackData& Data, FEffectProperties& EffectProperties) const;
};


