// Copyright Lede Studios. All Rights Reserved.


#include "PlayerCharacter.h"
#include "AbilitySystemGlobals.h"
#include "AbilitySystem/Component/DsAbilitySystemComponent.h"
#include "GameFramework/PlayerState.h"

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AbilitySystemComponent = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetPlayerState());

	if (UDsAbilitySystemComponent* Component = Cast<UDsAbilitySystemComponent>(AbilitySystemComponent))
	{
		Component->InitializeAbilitySystemData(AbilitySystemInitializationData, this, this);
		PostInitializeAbilitySystem();
	}
}

void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	AbilitySystemComponent = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetPlayerState());

	if (UDsAbilitySystemComponent* Component = Cast<UDsAbilitySystemComponent>(AbilitySystemComponent))
	{
		Component->InitializeAbilitySystemData(AbilitySystemInitializationData, this, this);
		PostInitializeAbilitySystem();
	}
}