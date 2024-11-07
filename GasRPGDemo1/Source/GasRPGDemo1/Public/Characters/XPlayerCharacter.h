// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/XBaseCharacter.h"
#include "XPlayerCharacter.generated.h"

class AXHUD;
/**
 * 
 */
UCLASS()
class GASRPGDEMO1_API AXPlayerCharacter : public AXBaseCharacter
{
	GENERATED_BODY()

public:
	AXPlayerCharacter();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

#pragma region Combat Interface
	virtual float GetCurLevel() override;
#pragma endregion
	
	UPROPERTY()
	AXHUD* XHUD;

protected:
	virtual void BeginPlay() override;
	
	virtual void InitialAbilityActorInfo() override;
};
