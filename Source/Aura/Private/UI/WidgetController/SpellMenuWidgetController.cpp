// Copyright Huibaekim


#include "UI/WidgetController/SpellMenuWidgetController.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "Player/AuraPlayerState.h"

void USpellMenuWidgetController::BroadcastInitialValues()
{
	BroadcastAbilityInfo();
	SpellPointsChanged.Broadcast(GetAuraPS()->GetSpellPoints());
}

void USpellMenuWidgetController::BindCallbacksToDependencies()
{
	GetAuraASC()->AbilityStatusChangedDelegate.AddLambda([this](const FGameplayTag& AbilityTag, const FGameplayTag& StatusTag)
	{
		if (SelectedAbility.Ability.MatchesTagExact(AbilityTag))
		{
			SelectedAbility.Status = StatusTag;

			bool bEnableSpendPoints = false;
			bool bEnableEquip = false;
			ShouldEnableButtons(StatusTag, CurrentSpellPoints, bEnableSpendPoints, bEnableEquip);

			SpellGlobeSelectedDelegate.Broadcast(bEnableSpendPoints, bEnableEquip);
		}
		
		if (AbilityInfo)
		{
			auto Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);
			Info.StatusTag = StatusTag;
			AbilityInfoDelegate.Broadcast(Info);
		}
	});	

	GetAuraPS()->OnSpellPointsChangedDelegate.AddLambda([this](int32 SpellPoints)
	{
		SpellPointsChanged.Broadcast(SpellPoints);
		CurrentSpellPoints = SpellPoints;

		bool bEnableSpendPoints = false;
		bool bEnableEquip = false;
		ShouldEnableButtons(SelectedAbility.Status, CurrentSpellPoints, bEnableSpendPoints, bEnableEquip);

		SpellGlobeSelectedDelegate.Broadcast(bEnableSpendPoints, bEnableEquip);
	});
}

void USpellMenuWidgetController::SpellGlobeSelected(const FGameplayTag& AbilityTag)
{
	const auto GameplayTags = FAuraGameplayTags::Get();
	const auto SpellPoints = GetAuraPS()->GetSpellPoints();
	FGameplayTag AbilityStatus;

	bool bTagValid = AbilityTag.IsValid();
	bool bTagNone = AbilityTag.MatchesTag(GameplayTags.Abilities_None);
	auto AbilitySpec = GetAuraASC()->GetSpecFromAbilityTag(AbilityTag);
	bool bSpecValid = AbilitySpec != nullptr; 
	if (false == bTagValid || bTagNone || false == bSpecValid)
	{
		AbilityStatus = GameplayTags.Abilities_Status_Locked;
	}
	else
	{
		AbilityStatus = GetAuraASC()->GetStatusFromSpec(*AbilitySpec);
	}

	SelectedAbility.Ability = AbilityTag;
	SelectedAbility.Status = AbilityStatus;
	
	bool bEnableSpendPoints = false;
	bool bEnableEquip = false;
	ShouldEnableButtons(AbilityStatus, SpellPoints, bEnableSpendPoints, bEnableEquip);

	SpellGlobeSelectedDelegate.Broadcast(bEnableSpendPoints, bEnableEquip);
}

void USpellMenuWidgetController::ShouldEnableButtons(const FGameplayTag& AbilityStatus, int32 SpellPoints,
	bool& bShouldEnableSpellPointsButton, bool& bShouldEnableEquipButton)
{
	bShouldEnableSpellPointsButton = false;
	bShouldEnableEquipButton = false;

	const auto GameplayTags = FAuraGameplayTags::Get();
	if (AbilityStatus.MatchesTagExact(GameplayTags.Abilities_Status_Equipped))
	{
		if (SpellPoints > 0)
			bShouldEnableSpellPointsButton = true;

		bShouldEnableEquipButton = true;
	}
	else if (AbilityStatus.MatchesTagExact(GameplayTags.Abilities_Status_Eligible))
	{
		if (SpellPoints > 0)
			bShouldEnableSpellPointsButton = true;
	}
	else if (AbilityStatus.MatchesTagExact(GameplayTags.Abilities_Status_Unlocked))
	{
		if (SpellPoints > 0)
			bShouldEnableSpellPointsButton = true;

		bShouldEnableEquipButton = true;
	}
}
