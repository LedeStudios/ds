// Copyright Lede Studios. All Rights Reserved.


#include "PlayerStateBase.h"

#include "AbilitySystem/Component/DsAbilitySystemComponent.h"

APlayerStateBase::APlayerStateBase()
{
	SetNetUpdateFrequency(100.f);
	
	AbilitySystemComponent = CreateDefaultSubobject<UDsAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
}

UAbilitySystemComponent* APlayerStateBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
