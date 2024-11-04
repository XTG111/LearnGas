// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/XWidgetController.h"
#include "OverlayWidgetController.generated.h"

class UXUserWidget;
struct FOnAttributeChangeData;

//the struct use for show tag's info in ui
USTRUCT(BlueprintType)
struct FUIWidgetRow: public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag(); // from the asc delegate FEffecAssetTags
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Message = FText();
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UXUserWidget> MessageWidget; // the tag show
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* MessageTexture2D = nullptr; // the icon
};

//begin Delegate use for trans new value to widget
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature,float,newvalue);
//end

//begin Delegate use for trans effect tag struct to widget
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature,FUIWidgetRow,row);
//end



/**
 * 
 */
UCLASS(Blueprintable,BlueprintType)
class GASRPGDEMO1_API UOverlayWidgetController : public UXWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadCastInitValue() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable,Category="GAS|Attribute")
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable,Category="GAS|Attribute")
	FOnAttributeChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable,Category="GAS|Attribute")
	FOnAttributeChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable,Category="GAS|Attribute")
	FOnAttributeChangedSignature OnMaxManaChanged;

	UPROPERTY(BlueprintAssignable,Category="GAS|Message")
	FMessageWidgetRowSignature MessageWidgetRowSignature;

protected:
	//the DataTable use -- need add in editor
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category="Widget Data")
	TObjectPtr<UDataTable> MessageWidgetDataTable;

	//Find Row by tag
	template<typename T>
	T* GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag);
	
};

template <typename T>
T* UOverlayWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	T* Row = DataTable->FindRow<T>(Tag.GetTagName(),TEXT("")); // 在DataTable中，设置了RowName 和 TagName一致
	if(Row) return Row;
	return nullptr;
}
