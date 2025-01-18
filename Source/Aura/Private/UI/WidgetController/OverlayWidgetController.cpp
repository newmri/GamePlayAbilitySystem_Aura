// Copyright Huibaekim


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "AbilitySystem/Data/LevelUpInfo.h"
#include "Player/AuraPlayerState.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const auto AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());

	OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const auto AuraPlayerState = CastChecked<AAuraPlayerState>(PlayerState);
	AuraPlayerState->OnXPChangedDelegate.AddUObject(this, &UOverlayWidgetController::OnXPChanged);
	AuraPlayerState->OnLevelChangedDelegate.AddLambda(
		[this](int32 NewLevel)
		{
			OnPlayerLevelChangedDelegate.Broadcast(NewLevel);
		}
	);
	
	const auto AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxManaChanged.Broadcast(Data.NewValue);
		}
	);

	if (auto AuraASC = Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent))
	{
		if (AuraASC->bStartupAbilitiesGiven)
			OnInitializeStartupAbilities(AuraASC);
		else
			AuraASC->AbilitiesGivenDelegate.AddUObject(this, &UOverlayWidgetController::OnInitializeStartupAbilities);
	
		AuraASC->EffectAssetTags.AddLambda(
			[this](const FGameplayTagContainer& AssetTags)
			{
				for (const auto& Tag : AssetTags)
				{
					auto MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));

					if (false == Tag.MatchesTag(MessageTag))
					{
						continue;
					}

					auto Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
					MessageWidgetRowDelegate.Broadcast(*Row);
				}
			}
		);
	}
}

void UOverlayWidgetController::OnInitializeStartupAbilities(UAuraAbilitySystemComponent* AuraAbilitySystemComponent)
{
	if (!AuraAbilitySystemComponent->bStartupAbilitiesGiven)
		return;

	FForEachAbility BroadcastDelegate;
	BroadcastDelegate.BindLambda([this, AuraAbilitySystemComponent](const FGameplayAbilitySpec& AbilitySpec)
	{
		auto Info = AbilityInfo->FindAbilityInfoForTag(AuraAbilitySystemComponent->GetAbilityTagFromSpec(AbilitySpec));
		Info.InputTag = AuraAbilitySystemComponent->GetInputTagFromSpec(AbilitySpec);
		AbilityInfoDelegate.Broadcast(Info);
	});
	AuraAbilitySystemComponent->ForEachAbility(BroadcastDelegate);
}

void UOverlayWidgetController::OnXPChanged(int32 NewXP) const
{
	const auto AuraPlayerState = CastChecked<AAuraPlayerState>(PlayerState);
	const auto LevelUpInfo = AuraPlayerState->LevelUpInfo;
	
	checkf(LevelUpInfo, TEXT("Unable to find LevelUpInfo"));
	
	auto Level = LevelUpInfo->FindLevelForXP(NewXP);
	auto MaxLevel = LevelUpInfo->LevelUpInfo.Num() + 1;
	
	if (Level <= MaxLevel && Level >= 1)
	{
		int32 LevelUpInfoIndex = Level - 1;
		const auto LevelUpRequirement = LevelUpInfo->LevelUpInfo[LevelUpInfoIndex].LevelUpRequirement;
		const auto PreviousLevelUpRequirement = Level >= 2 ? LevelUpInfo->LevelUpInfo[Level - 2].LevelUpRequirement : 0;

		const auto DeltaLevelRequirement = LevelUpRequirement - PreviousLevelUpRequirement;
		const auto XPForThisLevel = NewXP - PreviousLevelUpRequirement;

		const auto XPBarPercent = static_cast<float>(XPForThisLevel) / DeltaLevelRequirement;
		OnXPPercentChangedDelegate.Broadcast(XPBarPercent);
	}
	
}
