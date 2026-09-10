#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "MalAbilitySystemComponent.generated.h"

UCLASS()
class UNLUA_TEST_API UMalAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UMalAbilitySystemComponent();

	void AddCharacterAbilities(TArray<TSubclassOf<UGameplayAbility>> Abilities);

	void AbilityInputPressed(FGameplayTag InputTag);
	void AbilityInputReleased(FGameplayTag InputTag);
	void AbilityInputHeld(FGameplayTag InputTag);
};
