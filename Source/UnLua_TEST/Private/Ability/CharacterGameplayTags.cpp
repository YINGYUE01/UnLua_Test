#include "Ability/CharacterGameplayTags.h"

#include "GameplayTagsManager.h"

FCharacterGameplayTags FCharacterGameplayTags::GameplayTags;

const FCharacterGameplayTags& FCharacterGameplayTags::Get()
{
	return GameplayTags;
}

void FCharacterGameplayTags::InitializeNativeTags()
{
	GameplayTags.Attribute_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Primary.Strength"),FString("Increase physical damage"));
	GameplayTags.Attribute_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Primary.Vigor"),FString("Increase Health"));
	GameplayTags.Attribute_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.MaxHealth"),FString("Increase Health"));
	GameplayTags.Attribute_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.MaxMana"),FString("Increase Mana"));
	
}
