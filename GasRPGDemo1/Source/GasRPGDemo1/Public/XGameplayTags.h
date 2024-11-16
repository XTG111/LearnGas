// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 *
 *利用单例模式创建
 *native gameplay tags
 * 在cpp中创建tag，并添加到引擎中，使得可以在cpp中也可以使用tag
 */

struct XGameplayTags
{
public:
 static const XGameplayTags& GetInstance() { return GameplayTags; } //get struct ins
 static void InitializeNativeGameplayTags(); // initial the params
 
 // gameplaytag params
#pragma region Primary Tags
 FGameplayTag Attributes_Primary_Strength;
 FGameplayTag Attributes_Primary_Intelligence;
 FGameplayTag Attributes_Primary_Resilience;
 FGameplayTag Attributes_Primary_Vigor;
#pragma endregion
 
#pragma region Secondary Gameplay Tags
 FGameplayTag Attributes_Secondary_Armor;
 FGameplayTag Attributes_Secondary_ArmorPenetration;
 FGameplayTag Attributes_Secondary_BlockChance;
 FGameplayTag Attributes_Secondary_CriticalHitChance;
 FGameplayTag Attributes_Secondary_CriticalHitDamage;
 FGameplayTag Attributes_Secondary_CriticalHitResistance;
 FGameplayTag Attributes_Secondary_HealthRegeneration;
 FGameplayTag Attributes_Secondary_ManaRegeneration;
 FGameplayTag Attributes_Secondary_MaxHealth;
 FGameplayTag Attributes_Secondary_MaxMana;
#pragma endregion
 
protected:
private:
 static XGameplayTags GameplayTags;
};

