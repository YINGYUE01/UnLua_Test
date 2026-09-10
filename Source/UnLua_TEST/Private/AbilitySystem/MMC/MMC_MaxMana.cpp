// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MMC/MMC_MaxMana.h"

#include "AbilitySystem/MalAttributeSet.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	VigorCapture.AttributeToCapture = UMalAttributeSet::GetVigorAttribute();
	VigorCapture.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	VigorCapture.bSnapshot = false;
	RelevantAttributesToCapture.Add(VigorCapture);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTag = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTag = Spec.CapturedSourceTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTag;
	EvaluateParameters.TargetTags = TargetTag;
	float Magnitude = 0.0f;
	GetCapturedAttributeMagnitude(VigorCapture,Spec,EvaluateParameters,Magnitude);
	return 500 + 4*Magnitude;
}
