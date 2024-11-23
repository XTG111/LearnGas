// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "XInputConfigDataAsset.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FXInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	const class UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
};

UCLASS()
class GASRPGDEMO1_API UXInputConfigDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FXInputAction> InputActions;

	const UInputAction* GetInputActionByTag(const FGameplayTag InputTag, bool bIsNotFound = false) const;
};
