// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputConfig.h"


FAction* UInputConfig::GetActionByTag(const FGameplayTag& Tag)
{
	for (auto& Action : Actions)
	{
		if (Action.InputTag.MatchesTag(Tag))
		{
			return &Action;
		}
	}
	return nullptr;
}
