// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "DsAbilitySystemComponent.generated.h"

struct FAbilitySystemInitializationData;
/**
 * 
 */
UCLASS()
class DS_API UDsAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UDsAbilitySystemComponent();

protected:
	bool bIsAbilitySystemDataInitialized = false;
	
public:
	UFUNCTION(BlueprintCallable, Category="PB|Ability System Component")
	void InitializeAbilitySystemData(const FAbilitySystemInitializationData& InData, AActor* InOwningActor, AActor* InAvatarActor);

	const UAttributeSet* GetOrCreateAttributeSet(const TSubclassOf<UAttributeSet>& InAttributeSet);
	
};
