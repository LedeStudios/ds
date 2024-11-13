// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AbilitySystemFunctionLibrary.generated.h"

enum class EAttributeSearchType : uint8;
/**
 * 
 */
UCLASS()
class DS_API UAbilitySystemFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Ability System")
	static float GetAttributeValueFromActor(const AActor* Actor, const FGameplayAttribute Attribute, const EAttributeSearchType SearchType);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Ability System")
	static float GetAttributeValueFromAbilitySystem(const UAbilitySystemComponent* AbilitySystemComponent, const FGameplayAttribute Attribute, const EAttributeSearchType SearchType);

private:
	static void GetAttributeValue(const UAbilitySystemComponent* AbilitySystemComponent, const FGameplayAttribute& Attribute, const EAttributeSearchType SearchType, float& ReturnValue);
	
};
