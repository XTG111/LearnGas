// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStates/XPlayerState.h"
#include "AbilitySystems/XAbilitySystemComponent.h"
#include "AbilitySystems/XAttributeSet.h"
#include  "Net/UnrealNetwork.h"

AXPlayerState::AXPlayerState()
{
	NetUpdateFrequency = 100.0f;

	AbilitySystemComponent = CreateDefaultSubobject<UXAbilitySystemComponent>(TEXT("PlayerAbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UXAttributeSet>(TEXT("PlayerAttributeSet"));
}

UAbilitySystemComponent* AXPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AXPlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AXPlayerState, curLevel);
}

void AXPlayerState::OnRep_curLevel(float oldlevel)
{
}
