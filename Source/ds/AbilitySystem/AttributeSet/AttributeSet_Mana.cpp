// Copyright Lede Studios. All Rights Reserved.


#include "AttributeSet_Mana.h"

#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

UAttributeSet_Mana::UAttributeSet_Mana()
{
	MaximumMana = 0.f;
	CurrentMana = 0.f;
}

void UAttributeSet_Mana::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetMaximumManaAttribute())
	{
		AdjustAttributeForMaxChange(CurrentMana, MaximumMana, NewValue, GetCurrentManaAttribute());
	}
}

void UAttributeSet_Mana::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	const FGameplayAttribute Attribute = Data.EvaluatedData.Attribute;
	
	if (Attribute == GetDamageAttribute())
	{
		const float LocalDamage = GetDamage();
		
		SetDamage(0.f);
		
		if (LocalDamage > 0.f)
		{
			const float NewMana = GetCurrentMana() - LocalDamage;
			SetCurrentMana(FMath::Clamp(NewMana, 0.f, GetMaximumMana()));
		}
		return;
	}

	if (Attribute == GetHealingAttribute())
	{
		const float LocalHealing = GetHealing();

		SetHealing(0.f);

		if (LocalHealing > 0.f)
		{
			const float NewMana = GetCurrentMana() + LocalHealing;
			SetCurrentMana(FMath::Clamp(NewMana, 0.f, GetMaximumMana()));
		}
		return;
	}

	if (Attribute == GetCurrentManaAttribute())
	{
		SetCurrentMana(FMath::Clamp(GetCurrentMana(), 0.f, GetMaximumMana()));
		return;
	}
}

void UAttributeSet_Mana::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSet_Mana, CurrentMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSet_Mana, MaximumMana, COND_None, REPNOTIFY_Always);
}

void UAttributeSet_Mana::OnRep_CurrentMana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSet_Mana, CurrentMana, OldValue);
}

void UAttributeSet_Mana::OnRep_MaximumMana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSet_Mana, MaximumMana, OldValue);
}
