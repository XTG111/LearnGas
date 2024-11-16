// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "XAbilitySystemBPLibrary.generated.h"

class UXAttributeMenuWidgetController;
class UOverlayWidgetController;
/**
 * 
 */
UCLASS()
class GASRPGDEMO1_API UXAbilitySystemBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "XAbilitySystemBPFuncLibirary|WidgetController")
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "XAbilitySystemBPFuncLibirary|WidgetController")
	static UXAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);
};
