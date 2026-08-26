#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "Ability/CharacterAbilitySystemComponent.h"
#include "Ability/CharacterAttributeSet.h"
#include "CharacterPlayerState.generated.h"

UCLASS()
class UNLUA_TEST_API ACharacterPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ACharacterPlayerState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttribute()const {return AttributeSet;}
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability")
	TObjectPtr<UCharacterAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability")
	TObjectPtr<UCharacterAttributeSet> AttributeSet;
};
