// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/XPlayerCharacter.h"
#include "PlayerStates/XPlayerState.h"
#include "AbilitySystems/XAbilitySystemComponent.h"
#include "AbilitySystems/XAttributeSet.h"
#include "Controllers/XPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/HUD/XHUD.h"

AXPlayerCharacter::AXPlayerCharacter()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
}

void AXPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitialAbilityActorInfo(); // Initial Ability Actor Info for the server
}

void AXPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitialAbilityActorInfo();// Initial Ability Actor Info for the client
}

void AXPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AXPlayerCharacter::InitialAbilityActorInfo()
{
	AXPlayerState* XPlayerState = GetPlayerState<AXPlayerState>();
	if (XPlayerState)
	{
		XPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(XPlayerState, this);
		AbilitySystemComponent = XPlayerState->GetAbilitySystemComponent();
		AttributeSet = XPlayerState->GetAttributeSet();

		AXPlayerController* XPlayerController = GetController<AXPlayerController>();
		if(XPlayerController)
		{
			XHUD = Cast<AXHUD>(XPlayerController->GetHUD());
			if(XHUD) XHUD->InitOverlay(XPlayerController,XPlayerState,AbilitySystemComponent,AttributeSet);
		}
		
	}
}
