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
	
	//begin Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UXAttributeSet, Health);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UXAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UXAttributeSet, Mana);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Vital Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UXAttributeSet, MaxMana);
	//end Attributes
	

	//begin OnRep Func
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& oldhealth) const;
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& oldmaxhealth) const;

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& oldmana) const;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& oldmaxmana) const;
	//end OnRep Func

private:
	void SetFEffectProperties(const struct FGameplayEffectModCallbackData& Data, FEffectProperties& EffectProperties) const;
};
