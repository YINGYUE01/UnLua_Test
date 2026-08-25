#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "CharacterAttributeSet.generated.h"

UCLASS()
class UNLUA_TEST_API UCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UCharacterAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Attributes")
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Attributes")
	FGameplayAttributeData MaxHealth;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Stamina, Category = "Attributes")
	FGameplayAttributeData Stamina;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxStamina, Category = "Attributes")
	FGameplayAttributeData MaxStamina;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Attributes")
	FGameplayAttributeData Mana;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Attributes")
	FGameplayAttributeData MaxMana;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AttackPower, Category = "Attributes")
	FGameplayAttributeData AttackPower;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Defense, Category = "Attributes")
	FGameplayAttributeData Defense;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MoveSpeed, Category = "Attributes")
	FGameplayAttributeData MoveSpeed;

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth);

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldHealth);

	UFUNCTION()
	void OnRep_Stamina(const FGameplayAttributeData& OldHealth);

	UFUNCTION()
	void OnRep_MaxStamina(const FGameplayAttributeData& OldHealth);

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldHealth);

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldHealth);

	UFUNCTION()
	void OnRep_AttackPower(const FGameplayAttributeData& OldHealth);

	UFUNCTION()
	void OnRep_Defense(const FGameplayAttributeData& OldHealth);

	UFUNCTION()
	void OnRep_MoveSpeed(const FGameplayAttributeData& OldHealth);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UCharacterAttributeSet, Health)
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Health)
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Health)
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Health)

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UCharacterAttributeSet, MaxHealth)
	GAMEPLAYATTRIBUTE_VALUE_GETTER(MaxHealth)
	GAMEPLAYATTRIBUTE_VALUE_SETTER(MaxHealth)
	GAMEPLAYATTRIBUTE_VALUE_INITTER(MaxHealth)

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UCharacterAttributeSet, Stamina)
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Stamina)
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Stamina)
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Stamina)

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UCharacterAttributeSet, MaxStamina)
	GAMEPLAYATTRIBUTE_VALUE_GETTER(MaxStamina)
	GAMEPLAYATTRIBUTE_VALUE_SETTER(MaxStamina)
	GAMEPLAYATTRIBUTE_VALUE_INITTER(MaxStamina)

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UCharacterAttributeSet, Mana)
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Mana)
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Mana)
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Mana)

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UCharacterAttributeSet, MaxMana)
	GAMEPLAYATTRIBUTE_VALUE_GETTER(MaxMana)
	GAMEPLAYATTRIBUTE_VALUE_SETTER(MaxMana)
	GAMEPLAYATTRIBUTE_VALUE_INITTER(MaxMana)

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UCharacterAttributeSet, AttackPower)
	GAMEPLAYATTRIBUTE_VALUE_GETTER(AttackPower)
	GAMEPLAYATTRIBUTE_VALUE_SETTER(AttackPower)
	GAMEPLAYATTRIBUTE_VALUE_INITTER(AttackPower)

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UCharacterAttributeSet, Defense)
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Defense)
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Defense)
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Defense)

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UCharacterAttributeSet, MoveSpeed)
	GAMEPLAYATTRIBUTE_VALUE_GETTER(MoveSpeed)
	GAMEPLAYATTRIBUTE_VALUE_SETTER(MoveSpeed)
	GAMEPLAYATTRIBUTE_VALUE_INITTER(MoveSpeed)
};
