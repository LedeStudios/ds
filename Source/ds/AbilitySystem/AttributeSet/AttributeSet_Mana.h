// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSetBase.h"
#include "AttributeSet_Mana.generated.h"

/**
 * 
 */
UCLASS()
class DS_API UAttributeSet_Mana : public UAttributeSetBase
{
	GENERATED_BODY()

public:
	UAttributeSet_Mana();

public:
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
// ======================================================================================
//  Properties
// ======================================================================================
public:

	// Used to create a local copy of Damage which is then subtracted from Current Mana.
	UPROPERTY(BlueprintReadOnly, Category="Mana Attribute Set", meta=(HideFromLevelInfos))
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UAttributeSet_Mana, Damage)

	// Used to create a local copy of Healing which is then added to Current Mana.
	UPROPERTY(BlueprintReadOnly, Category="Mana Attribute Set", meta=(HideFromLevelInfos))
	FGameplayAttributeData Healing;
	ATTRIBUTE_ACCESSORS(UAttributeSet_Mana, Healing)

	// Holds the current value for Mana.
	UPROPERTY(BlueprintReadOnly, Category = "Mana Attribute Set", ReplicatedUsing = OnRep_CurrentMana)
	FGameplayAttributeData CurrentMana;
	ATTRIBUTE_ACCESSORS(UAttributeSet_Mana, CurrentMana)

	// Holds the value for Maximum Mana.
	UPROPERTY(BlueprintReadOnly, Category = "Mana Attribute Set", ReplicatedUsing = OnRep_MaximumMana)
	FGameplayAttributeData MaximumMana;
	ATTRIBUTE_ACCESSORS(UAttributeSet_Mana, MaximumMana)

// ======================================================================================
//  Replicates
// ======================================================================================
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
protected:
	
	UFUNCTION()
	virtual void OnRep_CurrentMana(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MaximumMana(const FGameplayAttributeData& OldValue);
	
};
