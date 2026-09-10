// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnLua_TEST.h"
#include "Modules/ModuleManager.h"
#include "AbilitySystem/MalGameplayTags.h"

class FUnLua_TESTGameModuleImpl : public FDefaultGameModuleImpl
{
public:
	virtual void StartupModule() override;
};

void FUnLua_TESTGameModuleImpl::StartupModule()
{
	FMalGameplayTags::InitializeNativeTags();
}

IMPLEMENT_PRIMARY_GAME_MODULE( FUnLua_TESTGameModuleImpl, UnLua_TEST, "UnLua_TEST" );
