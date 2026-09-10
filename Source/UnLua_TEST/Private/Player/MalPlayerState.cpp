#include "Player/MalPlayerState.h"

AMalPlayerState::AMalPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UMalAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UMalAttributeSet>(TEXT("AttributeSet"));
}


UAbilitySystemComponent* AMalPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
