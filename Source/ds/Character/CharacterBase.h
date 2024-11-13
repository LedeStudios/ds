// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/Data/AbilitySystemData.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

struct FAttributesData;

UCLASS()
class DS_API ACharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
// ======================================================================================
//  Init
// ======================================================================================
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Ability System", meta=(ShowOnlyInnerProperties))
	FAbilitySystemInitializationData AbilitySystemInitializationData;	
	
	UFUNCTION(BlueprintImplementableEvent)
	void PostInitializeAbilitySystem();
	
// ======================================================================================
//  Ability Systems
// ======================================================================================
protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

};
