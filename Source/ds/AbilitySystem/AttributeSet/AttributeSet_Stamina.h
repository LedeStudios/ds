// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSetBase.h"
#include "AttributeSet_Stamina.generated.h"

/**
 * 
 */
UCLASS()
class DS_API UAttributeSet_Stamina : public UAttributeSetBase
{
	GENERATED_BODY()

public:
	UAttributeSet_Stamina();

public:
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
// ======================================================================================
//  Properties
// ======================================================================================
public:

	// Used to create a local copy of Damage which is then subtracted from Current Stamina.
	UPROPERTY(BlueprintReadOnly, Category="Stamina Attribute Set", meta=(HideFromLevelInfos))
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UAttributeSet_Stamina, Damage)

	// Used to create a local copy of Healing which is then added to Current Stamina.
	UPROPERTY(BlueprintReadOnly, Category="Stamina Attribute Set", meta=(HideFromLevelInfos))
	FGameplayAttributeData Healing;
	ATTRIBUTE_ACCESSORS(UAttributeSet_Stamina, Healing)

	// Holds the current value for Stamina.
	UPROPERTY(BlueprintReadOnly, Category = "Stamina Attribute Set", ReplicatedUsing = OnRep_CurrentStamina)
	FGameplayAttributeData CurrentStamina;
	ATTRIBUTE_ACCESSORS(UAttributeSet_Stamina, CurrentStamina)

	// Holds the value for Maximum Stamina.
	UPROPERTY(BlueprintReadOnly, Category = "Stamina Attribute Set", ReplicatedUsing = OnRep_MaximumStamina)
	FGameplayAttributeData MaximumStamina;
	ATTRIBUTE_ACCESSORS(UAttributeSet_Stamina, MaximumStamina)

// ======================================================================================
//  Replicates
// ======================================================================================
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
protected:
	
	UFUNCTION()
	virtual void OnRep_CurrentStamina(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	virtual void OnRep_MaximumStamina(const FGameplayAttributeData& OldValue);
	
};
