// Copyright Lede Studios. All Rights Reserved.


#include "AttributeSet_Health.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

UAttributeSet_Health::UAttributeSet_Health()
{
	MaximumHealth = 0.f;
	CurrentHealth = 0.f;
}

void UAttributeSet_Health::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetMaximumHealthAttribute())
	{
		AdjustAttributeForMaxChange(CurrentHealth, MaximumHealth, NewValue, GetCurrentHealthAttribute());
	}
}

void UAttributeSet_Health::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	const FGameplayAttribute Attribute = Data.EvaluatedData.Attribute;
	
	if (Attribute == GetDamageAttribute())
	{
		const float LocalDamage = GetDamage();
		
		SetDamage(0.f);
		
		if (LocalDamage > 0.f)
		{
			const float NewHealth = GetCurrentHealth() - LocalDamage;
			SetCurrentHealth(FMath::Clamp(NewHealth, 0.f, GetMaximumHealth()));
		}
		return;
	}

	if (Attribute == GetHealingAttribute())
	{
		const float LocalHealing = GetHealing();

		SetHealing(0.f);

		if (LocalHealing > 0.f)
		{
			const float NewHealth = GetCurrentHealth() + LocalHealing;
			SetCurrentHealth(FMath::Clamp(NewHealth, 0.f, GetMaximumHealth()));
		}
		return;
	}

	if (Attribute == GetCurrentHealthAttribute())
	{
		SetCurrentHealth(FMath::Clamp(GetCurrentHealth(), 0.f, GetMaximumHealth()));
		return;
	}
}

void UAttributeSet_Health::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSet_Health, CurrentHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSet_Health, MaximumHealth, COND_None, REPNOTIFY_Always);
}

void UAttributeSet_Health::OnRep_CurrentHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSet_Health, CurrentHealth, OldValue);
}

void UAttributeSet_Health::OnRep_MaximumHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSet_Health, MaximumHealth, OldValue);
}
