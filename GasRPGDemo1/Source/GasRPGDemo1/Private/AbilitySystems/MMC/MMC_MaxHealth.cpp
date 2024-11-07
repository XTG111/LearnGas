// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystems/MMC/MMC_MaxHealth.h"

#include "AbilitySystems/XAttributeSet.h"
#include "Interaction/XCombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	//set vigordef
	VigorDef.AttributeToCapture = UXAttributeSet::GetVigorAttribute();
	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	VigorDef.bSnapshot = false;

	//RelevantAttributesToCapture is a TArray which 
	RelevantAttributesToCapture.Add(VigorDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	//GetCapturedAttributeMagnitude -- 通过vigordef获取当前vigor数值
	//GetCapturedAttributeMagnitude需要参数FAggregatorEvaluateParameters
	//FAggregatorEvaluateParameters通过设置sourcetag 和 targettag实现初始化

	//获取tag
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParams;
	EvaluateParams.SourceTags = SourceTags;
	EvaluateParams.TargetTags = TargetTags;
	
	float curvigor = 0.0f;
	GetCapturedAttributeMagnitude(VigorDef,Spec, EvaluateParams, curvigor);

	//获取level
	IXCombatInterface* CombatInterface = Cast<IXCombatInterface>(Spec.GetContext().GetSourceObject());
	const float curlevel = CombatInterface->GetCurLevel();

	//自定义计算公式
	return 80.f + 2.5f * curvigor + 10.f * curlevel;
}
