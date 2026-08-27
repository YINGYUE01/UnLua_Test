#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

class UNLUA_TEST_API FCharacterGameplayTags
{
public:
	static const FCharacterGameplayTags& Get();
	static void InitializeNativeTags();
	/*Attribute */
	FGameplayTag Attribute_Primary_Strength;
	FGameplayTag Attribute_Primary_Vigor;

	FGameplayTag Attribute_Secondary_MaxHealth;
	FGameplayTag Attribute_Secondary_MaxMana;

	/*Ability*/
	FGameplayTag Ability_Damage;
	FGameplayTag Ability_Attack;
private:
	static FCharacterGameplayTags GameplayTags;
};
