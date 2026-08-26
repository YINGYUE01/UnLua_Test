#include "Player/CharacterPlayerState.h"

ACharacterPlayerState::ACharacterPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UCharacterAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UCharacterAttributeSet>(TEXT("AttributeSet"));
}


UAbilitySystemComponent* ACharacterPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
