// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AttributeInfoDataAsset.generated.h"

//when attribute change will trans this struct then the UI will get the change and show
USTRUCT(BlueprintType)
struct FXAttributeInfo
{
	GENERATED_BODY()

	//which tag will change
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AttributeTag = FGameplayTag();
	//the Attribute Name in UI
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeName = FText();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeDescription = FText();
	UPROPERTY(BlueprintReadOnly)
	float AttributeValue = 0.0f;
};

/**
 * 
 */
UCLASS()
class GASRPGDEMO1_API UAttributeInfoDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	FXAttributeInfo FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound = false) const;

	//当前dataasset 存储的所有attribute信息
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FXAttributeInfo> AttributeInfos;
	
};
