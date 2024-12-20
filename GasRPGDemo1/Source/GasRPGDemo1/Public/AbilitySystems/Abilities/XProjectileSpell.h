// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystems/Abilities/XGameplayAbility.h"
#include "XProjectileSpell.generated.h"

class AXProjectile;
/**
 * 
 */
UCLASS()
class GASRPGDEMO1_API UXProjectileSpell : public UXGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Projectile")
	TSubclassOf<AXProjectile> ProjectileClass;
};
