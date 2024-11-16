// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystems/Data/AttributeInfoDataAsset.h"
#include "UI/WidgetController/XWidgetController.h"
#include "XAttributeMenuWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeValueChanged, FXAttributeInfo, AttributeInfo);

/**
 * 
 */
UCLASS(Blueprintable,BlueprintType)
class GASRPGDEMO1_API UXAttributeMenuWidgetController : public UXWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadCastInitValue() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeValueChanged OnAttributeValueChanged;

	
protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAttributeInfoDataAsset> AttributeInfoData;

private:
	void BoradCastAttributeInfo(const FGameplayTag& GameplayTag, const FGameplayAttribute& Attribute);
};
