// Copyright Huibaekim


#include "Actor/AuraEffectActor.h"
#include "Components/SphereComponent.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Kismet/KismetMathLibrary.h"

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

void AAuraEffectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RunningTime += DeltaTime;
	const float SinePeriod = 2 * PI / SinePeriodConstant;
	if (RunningTime > SinePeriod)
	{
		RunningTime = 0.0f;
	}

	ItemMovement(DeltaTime);
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	InitialLocation = GetActorLocation();
	CalculatedLocation = InitialLocation;
	CalculatedRotation = GetActorRotation();
}

void AAuraEffectActor::StartSinusoidalMovement()
{
	bSinusoidalMovement = true;
	InitialLocation = GetActorLocation();
	CalculatedLocation = InitialLocation;
}

void AAuraEffectActor::StartRotation()
{
	bRotates = true;
	CalculatedRotation = GetActorRotation();
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	if (TargetActor->ActorHasTag(FName("Enemy")) && false == bApplyEffectsToEnemies)
	{
		return;
	}

	auto TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (nullptr == TargetASC)
	{
		return;
	}

	check(GameplayEffectClass);

	auto EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	auto EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, ActorLevel, EffectContextHandle);
	auto ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	const auto bIsInfinite = EGameplayEffectDurationType::Infinite == EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy;
	if (bIsInfinite && EEffectRemovalPolicy::RemoveOnEndOverlap == InfiniteRemovalPolicy)
	{
		ActiveEffectHandles.Add(ActiveEffectHandle, TargetASC);
	}

	if (false == bIsInfinite)
	{
		Destroy();
	}
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	if (TargetActor->ActorHasTag(FName("Enemy")) && bApplyEffectsToEnemies)
	{
		return;
	}

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
	if (TargetActor->ActorHasTag(FName("Enemy")) && bApplyEffectsToEnemies)
	{
		return;
	}

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

void AAuraEffectActor::ItemMovement(float DeltaTime)
{
	if (bRotates)
	{
		const FRotator DeltaRotation(0.f, DeltaTime * RotationRate, 0.f);
		CalculatedRotation = UKismetMathLibrary::ComposeRotators(CalculatedRotation, DeltaRotation);
	}
	if (bSinusoidalMovement)
	{
		const float Sine = SineAmplitude * FMath::Sin(RunningTime * SinePeriodConstant);
		CalculatedLocation = InitialLocation + FVector(0.0f, 0.f, Sine);
	}
}


