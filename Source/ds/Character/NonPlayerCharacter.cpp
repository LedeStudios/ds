// Copyright Lede Studios. All Rights Reserved.


#include "NonPlayerCharacter.h"

#include "AbilitySystem/Component/DsAbilitySystemComponent.h"

ANonPlayerCharacter::ANonPlayerCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UDsAbilitySystemComponent>("AbilitySystemComponent");
}

void ANonPlayerCharacter::BeginPlay()
{
	if (UDsAbilitySystemComponent* Component = Cast<UDsAbilitySystemComponent>(AbilitySystemComponent))
	{
		Component->InitializeAbilitySystemData(AbilitySystemInitializationData, this, this);
		PostInitializeAbilitySystem();
	}

	Super::BeginPlay();
}
