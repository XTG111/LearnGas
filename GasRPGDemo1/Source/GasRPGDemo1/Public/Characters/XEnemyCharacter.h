// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/XBaseCharacter.h"
#include "Interaction/EnemyInterface.h"
#include "XEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class GASRPGDEMO1_API AXEnemyCharacter : public AXBaseCharacter, public IEnemyInterface
{
	GENERATED_BODY()
public:
	AXEnemyCharacter();

protected:
	virtual void BeginPlay() override;

	virtual void InitialAbilityActorInfo() override;

public:
#pragma region Enemy Interface
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
#pragma endregion

#pragma region Combat Interface
	virtual float GetCurLevel() override;
#pragma endregion

	UPROPERTY(BlueprintReadOnly)
	bool bHighlight = false;

	//AI Enemy level can be changed easily in editor
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Class Default")
	float curLevel = 1.0f;
};
