// Copyright Lede Studios. All Rights Reserved.


#include "AbilitySystemFunctionLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "AbilitySystem/Data/AbilitySystemData.h"

float UAbilitySystemFunctionLibrary::GetAttributeValueFromActor(const AActor* Actor, const FGameplayAttribute Attribute,
                                                                const EAttributeSearchType SearchType)
{
	float ReturnValue = -1.f;
	if (const UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Actor))
	{
		GetAttributeValue(AbilitySystemComponent, Attribute, SearchType, ReturnValue);
	}
	return ReturnValue;
}

float UAbilitySystemFunctionLibrary::GetAttributeValueFromAbilitySystem(
	const UAbilitySystemComponent* AbilitySystemComponent, const FGameplayAttribute Attribute,
	const EAttributeSearchType SearchType)
{
	float ReturnValue = -1.f;
	GetAttributeValue(AbilitySystemComponent, Attribute, SearchType, ReturnValue);
	return ReturnValue;
}

void UAbilitySystemFunctionLibrary::GetAttributeValue(const UAbilitySystemComponent* AbilitySystemComponent,
	const FGameplayAttribute& Attribute, const EAttributeSearchType SearchType, float& ReturnValue)
{
	ReturnValue = -1.f;
	if (!AbilitySystemComponent || !AbilitySystemComponent->HasAttributeSetForAttribute(Attribute))
	{
		return;
	}

	switch (SearchType)
	{
	case EAttributeSearchType::FinalValue :
		{
			ReturnValue = AbilitySystemComponent->GetNumericAttribute(Attribute);
			break;
		}
	case EAttributeSearchType::BaseValue :
		{
			ReturnValue = AbilitySystemComponent->GetNumericAttributeBase(Attribute);
			break;
		}
	case EAttributeSearchType::BonusValue :
		{
			ReturnValue = AbilitySystemComponent->GetNumericAttribute(Attribute) - AbilitySystemComponent->GetNumericAttributeBase(Attribute);
			break;
		}
	}
}
