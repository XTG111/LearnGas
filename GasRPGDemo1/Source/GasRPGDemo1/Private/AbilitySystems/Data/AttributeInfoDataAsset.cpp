// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystems/Data/AttributeInfoDataAsset.h"

#include "AttributeSet.h"

FXAttributeInfo UAttributeInfoDataAsset::FindAttributeInfoForTag(const FGameplayTag& AttributeTag,
                                                                 bool bLogNotFound) const
{
	for(const FXAttributeInfo& AttributeInfo : AttributeInfos)
	{
		if(AttributeInfo.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return AttributeInfo;
		}
	}
	if(bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("AttributeTag [%s] not found on this DataAsset [%s]"), *AttributeTag.ToString(), *GetNameSafe(this));
	}

	return FXAttributeInfo();
}
