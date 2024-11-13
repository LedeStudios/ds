// Copyright Lede Studios. All Rights Reserved.


#include "AttributeSetBase.h"

#include "AbilitySystemComponent.h"

void UAttributeSetBase::AdjustAttributeForMaxChange(const FGameplayAttributeData& AffectedAttribute,
                                                    const FGameplayAttributeData& MaxAttribute, float NewMaxValue,
                                                    const FGameplayAttribute& AffectedAttributeProperty) const
{
	if (UAbilitySystemComponent* AbilitySystemComponent = GetOwningAbilitySystemComponent())
	{
		if (const float CurrentMaxValue = MaxAttribute.GetCurrentValue(); !FMath::IsNearlyEqual(CurrentMaxValue, NewMaxValue))
		{
			// Change current value to maintain the Current Value / Maximum Value percentage.
			const float CurrentValue = AffectedAttribute.GetCurrentValue();
			const float NewDelta = CurrentMaxValue > 0.f ? CurrentValue * NewMaxValue / CurrentMaxValue - CurrentValue : NewMaxValue;
			AbilitySystemComponent->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
		}
	}
}
