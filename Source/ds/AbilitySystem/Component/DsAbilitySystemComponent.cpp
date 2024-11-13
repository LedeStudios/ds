// Copyright Lede Studios. All Rights Reserved.


#include "DsAbilitySystemComponent.h"

#include "AbilitySystem/Data/AbilitySystemData.h"

UDsAbilitySystemComponent::UDsAbilitySystemComponent()
{
	ReplicationMode = EGameplayEffectReplicationMode::Mixed;
	SetIsReplicatedByDefault(true);
}

void UDsAbilitySystemComponent::InitializeAbilitySystemData(const FAbilitySystemInitializationData& InData,
	AActor* InOwningActor, AActor* InAvatarActor)
{
	if (bIsAbilitySystemDataInitialized)
	{
		return;
	}
	
	bIsAbilitySystemDataInitialized = true;

	// OwningActor = 어빌리티를 소유할 액터,  AvatarActor = 어빌리티가 적용될 액터
	InitAbilityActorInfo(InOwningActor, InAvatarActor);

	// 권한이 있는지 확인 (생성된 게임플레이 오브젝트는 자동으로 클라이언트이 리플리케이션 됨)
	if (GetOwnerActor()->HasAuthority())
	{
		// AttributeSet 등록
		for (const TSubclassOf<UAttributeSet> AttributeSet : InData.AttributeSets)
		{
			GetOrCreateAttributeSet(AttributeSet);
		}

		// Attribute Base Value 반영
		for (const TTuple<FGameplayAttribute, float> AttributeBaseValue : InData.AttributeBaseValues)
		{
			if (HasAttributeSetForAttribute(AttributeBaseValue.Key))
			{
				SetNumericAttributeBase(AttributeBaseValue.Key, AttributeBaseValue.Value);
			}
		}

		// Gameplay Abilities 등록
		for (const TSubclassOf<UGameplayAbility> GameplayAbility : InData.GameplayAbilities)
		{
			FGameplayAbilitySpec Spec = FGameplayAbilitySpec(GameplayAbility, 1, INDEX_NONE, this);
			GiveAbility(Spec);
		}

		// Gameplay Effects 등록
		for (const TSubclassOf<UGameplayEffect> GameplayEffect : InData.GameplayEffects)
		{
			if (IsValid(GameplayEffect))
			{
				FGameplayEffectContextHandle Handle = MakeEffectContext();
				Handle.AddSourceObject(this);

				if (FGameplayEffectSpecHandle SpecHandle = MakeOutgoingSpec(GameplayEffect, 1, Handle); SpecHandle.IsValid())
				{
					ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), this);
				}
			}
		}
	}

	// 게임플레이 태그는 서버와 클라이언트 모두에 직접 적용해야 함
	if (!InData.GameplayTags.IsEmpty())
	{
		AddLooseGameplayTags(InData.GameplayTags);
	}
}

const UAttributeSet* UDsAbilitySystemComponent::GetOrCreateAttributeSet(
	const TSubclassOf<UAttributeSet>& InAttributeSet)
{
	return GetOrCreateAttributeSubobject(InAttributeSet);
}
