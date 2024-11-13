// Copyright Lede Studios. All Rights Reserved.

#include "AttributeSet_Stamina.h"

#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

UAttributeSet_Stamina::UAttributeSet_Stamina()
{
	MaximumStamina = 0.f;
	CurrentStamina = 0.f;
}

void UAttributeSet_Stamina::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetMaximumStaminaAttribute())
	{
		AdjustAttributeForMaxChange(CurrentStamina, MaximumStamina, NewValue, GetCurrentStaminaAttribute());
	}
}

void UAttributeSet_Stamina::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	const FGameplayAttribute Attribute = Data.EvaluatedData.Attribute;
	
	if (Attribute == GetDamageAttribute())
	{
		const float LocalDamage = GetDamage();
		
		SetDamage(0.f);
		
		if (LocalDamage > 0.f)
		{
			const float NewStamina = GetCurrentStamina() - LocalDamage;
			SetCurrentStamina(FMath::Clamp(NewStamina, 0.f, GetMaximumStamina()));
		}
		return;
	}

	if (Attribute == GetHealingAttribute())
	{
		const float LocalHealing = GetHealing();

		SetHealing(0.f);

		if (LocalHealing > 0.f)
		{
			const float NewStamina = GetCurrentStamina() + LocalHealing;
			SetCurrentStamina(FMath::Clamp(NewStamina, 0.f, GetMaximumStamina()));
		}
		return;
	}

	if (Attribute == GetCurrentStaminaAttribute())
	{
		SetCurrentStamina(FMath::Clamp(GetCurrentStamina(), 0.f, GetMaximumStamina()));
		return;
	}
}

void UAttributeSet_Stamina::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSet_Stamina, CurrentStamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSet_Stamina, MaximumStamina, COND_None, REPNOTIFY_Always);
}

void UAttributeSet_Stamina::OnRep_CurrentStamina(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSet_Stamina, CurrentStamina, OldValue);
}

void UAttributeSet_Stamina::OnRep_MaximumStamina(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSet_Stamina, MaximumStamina, OldValue);
}
