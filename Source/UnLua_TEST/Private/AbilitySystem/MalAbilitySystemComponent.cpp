#include "AbilitySystem/MalAbilitySystemComponent.h"

#include "AbilitySystem/Ability/MalGameplayAbility.h"

UMalAbilitySystemComponent::UMalAbilitySystemComponent()
{
	SetIsReplicatedByDefault(true);
}

void UMalAbilitySystemComponent::AddCharacterAbilities(TArray<TSubclassOf<UGameplayAbility>> Abilities)
{
	for (TSubclassOf<UGameplayAbility> Ability : Abilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability,1);
		UMalGameplayAbility* MalAbility = Cast<UMalGameplayAbility>(AbilitySpec.Ability);
		if (MalAbility)
		{
			AbilitySpec.DynamicAbilityTags.AddTag(MalAbility->StartInputTag);
			GiveAbility(AbilitySpec);
		}
	}
}

void UMalAbilitySystemComponent::AbilityInputPressed(FGameplayTag InputTag)
{
	for (auto& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag) && AbilitySpec.IsActive())
		{
			AbilitySpecInputPressed(AbilitySpec);
		}
	}
}


void UMalAbilitySystemComponent::AbilityInputReleased(FGameplayTag InputTag)
{
	for (auto& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(AbilitySpec);
		}
	}
}

void UMalAbilitySystemComponent::AbilityInputHeld(FGameplayTag InputTag)
{
	for (auto& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if (!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
			
		}
		
	}
}
