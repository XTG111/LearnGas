// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystems/MMC/MMC_MaxMana.h"

#include "AbilitySystems/XAttributeSet.h"
#include "Interaction/XCombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	IntelligenceDef.AttributeToCapture = UXAttributeSet::GetIntelligenceAttribute();
	IntelligenceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntelligenceDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(IntelligenceDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	
	FAggregatorEvaluateParameters EvaluateParams;
	EvaluateParams.SourceTags = SourceTags;
	EvaluateParams.TargetTags = TargetTags;
	
	float IntelligenceValue = 0.f;
	GetCapturedAttributeMagnitude(IntelligenceDef,Spec, EvaluateParams, IntelligenceValue);
	
	IXCombatInterface* CombatInterface = Cast<IXCombatInterface>(Spec.GetContext().GetSourceObject());
	float curlevel = CombatInterface->GetCurLevel();

	return 50.0f + 2.5*IntelligenceValue + 15*curlevel;
}
