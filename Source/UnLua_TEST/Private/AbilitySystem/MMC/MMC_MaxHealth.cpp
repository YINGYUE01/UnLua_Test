// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem//MMC/MMC_MaxHealth.h"

#include "AbilitySystem/CharacterAttributeSet.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	VigorCapture.AttributeToCapture = UCharacterAttributeSet::GetVigorAttribute();
	VigorCapture.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	VigorCapture.bSnapshot = false;
	RelevantAttributesToCapture.Add(VigorCapture);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTag = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTag = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTag;
	EvaluateParameters.TargetTags = TargetTag;
	float Magnitude = 0.f;
	GetCapturedAttributeMagnitude(VigorCapture,Spec,EvaluateParameters,Magnitude);
	return 100 + 0.5f * Magnitude;
}
