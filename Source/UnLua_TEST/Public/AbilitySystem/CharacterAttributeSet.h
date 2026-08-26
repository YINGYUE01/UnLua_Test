#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "CharacterAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName,PropertyName)\
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)\
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName)\
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
		
UCLASS()
class UNLUA_TEST_API UCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UCharacterAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;


	/* vital Attributes Begin */
	//生命值
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Attributes")
	FGameplayAttributeData Health;
	//法力值
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Attributes")
	FGameplayAttributeData Mana;
	//攻击力
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AttackPower, Category = "Attributes")
	FGameplayAttributeData AttackPower;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MoveSpeed, Category = "Attributes")
	FGameplayAttributeData MoveSpeed;
	/* vital Attributes End */


	/* Secondary Attribute Begin */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Attributes")
	FGameplayAttributeData MaxHealth;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxStamina, Category = "Attributes")
	FGameplayAttributeData MaxStamina;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Attributes")
	FGameplayAttributeData MaxMana;
	//耐力
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Stamina, Category = "Attributes")
	FGameplayAttributeData Stamina;
	//防御
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Defense, Category = "Attributes")
	FGameplayAttributeData Defense;
	/* Secondary Attribute End */


	/* Primary Attribute Begin*/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "Attributes")
	FGameplayAttributeData Strength;
	UPROPERTY(BlueprintReadOnly, Replicated=OnRep_Vigor, Category = "Attributes")
	FGameplayAttributeData Vigor;
	/* Primary Attribute End*/
	
	
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

	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength);
	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldVigor);

	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Health)
	
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, MaxHealth)
	
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Stamina)
	
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, MaxStamina)
	
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Mana)
	
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, MaxMana)
	
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, AttackPower)
	
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Defense)
	
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, MoveSpeed)

	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet,Strength);
	
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet,Vigor);
};
