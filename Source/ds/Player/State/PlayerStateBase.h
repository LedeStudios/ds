// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "PlayerStateBase.generated.h"


class UDsAbilitySystemComponent;

UCLASS()
class DS_API APlayerStateBase : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	APlayerStateBase();

// ======================================================================================
// Ability Systems
// ======================================================================================
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DS")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	

	
};
