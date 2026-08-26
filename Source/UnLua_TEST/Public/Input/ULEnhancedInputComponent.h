// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "InputConfig.h"
#include "ULEnhancedInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class UNLUA_TEST_API UULEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
public:
	template<class UserClass,typename PressedFuncType,typename ReleasedFuncType,typename HeldFuncType>
	void BindAbilityActions(const class UInputConfig* InputConfig,UserClass* Object,PressedFuncType PressedFunc,ReleasedFuncType ReleasedFunc,HeldFuncType HeldFunc);

};
template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UULEnhancedInputComponent::BindAbilityActions(const class UInputConfig* InputConfig, UserClass* Object,
	PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	if (!InputConfig)
	{
		return;
	}
	for (const FAction& Action : InputConfig->Actions)
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindAction(Action.InputAction,ETriggerEvent::Started,Object,PressedFunc,Action.InputTag);
			}
			if (ReleasedFunc)
			{
				BindAction(Action.InputAction,ETriggerEvent::Completed,Object,ReleasedFunc,Action.InputTag);
			}
			if (HeldFunc)
			{
				BindAction(Action.InputAction,ETriggerEvent::Triggered,Object,HeldFunc,Action.InputTag);
			}
		}
	}
}
