// Copyright Huibaekim


#include "Actor/AuraEffectActor.h"
#include "Components/SphereComponent.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	auto TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (nullptr == TargetASC)
	{
		return;
	}

	check(GameplayEffectClass);

	auto EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	auto EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1.f, EffectContextHandle);
	auto ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	const auto bIsInfinite = EGameplayEffectDurationType::Infinite == EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy;
	if (bIsInfinite && EEffectRemovalPolicy::RemoveOnEndOverlap == InfiniteRemovalPolicy)
	{
		ActiveEffectHandles.Add(ActiveEffectHandle, TargetASC);
	}
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	if (EEffectApplicationPolicy::ApplyOnOverlap == InstantApplicationPolicy)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}
	if (EEffectApplicationPolicy::ApplyOnOverlap == DurationApplicationPolicy)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	if (EEffectApplicationPolicy::ApplyOnOverlap == InfiniteApplicationPolicy)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (EEffectApplicationPolicy::ApplyOnEndOverlap == InstantApplicationPolicy)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}
	if (EEffectApplicationPolicy::ApplyOnEndOverlap == DurationApplicationPolicy)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	if (EEffectApplicationPolicy::ApplyOnEndOverlap == InfiniteApplicationPolicy)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
	if (EEffectRemovalPolicy::RemoveOnEndOverlap == InfiniteRemovalPolicy)
	{
		auto TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (nullptr == TargetASC)
		{
			return;
		}

		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		for (auto& d : ActiveEffectHandles)
		{
			if (TargetASC == d.Value)
			{
				TargetASC->RemoveActiveGameplayEffect(d.Key, 1);
				HandlesToRemove.Add(d.Key);
			}
		}

		for (auto& d : HandlesToRemove)
		{
			ActiveEffectHandles.FindAndRemoveChecked(d);
		}
	}
}


