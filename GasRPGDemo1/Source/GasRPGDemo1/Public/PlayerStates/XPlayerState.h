// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "XPlayerState.generated.h"

/**
 * 
 */

class UAbilitySystemComponent;
class UAttributeSet;

UCLASS()
class GASRPGDEMO1_API AXPlayerState : public APlayerState,public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	AXPlayerState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	FORCEINLINE float GetPlayerCurLevel() const { return curLevel; }
protected:
	//GAS -- For Player
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	
private:
	//player level need be changed by the gamestate
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_curLevel,Category = "Level")
	float curLevel = 1.0f;

	UFUNCTION()
	void OnRep_curLevel(float oldlevel);
};
