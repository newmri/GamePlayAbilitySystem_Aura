// Copyright Huibaekim


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "Player/AuraPlayerState.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	auto AS = CastChecked<UAuraAttributeSet>(AttributeSet);

	for (auto& d : AS->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(d.Value()).AddLambda(
			[this, d](const FOnAttributeChangeData& Data)
			{
				BroadcastAttributeInfo(d.Key, d.Value());
			}
		);
	}

	auto AuraPlayerState = CastChecked<AAuraPlayerState>(PlayerState);
	AuraPlayerState->OnAttributePointsChangedDelegate.AddLambda(
		[this](int32 Points)
		{
			AttributePointsChangedDelegate.Broadcast(Points);
		});
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	auto AS = CastChecked<UAuraAttributeSet>(AttributeSet);

	check(AttributeInfo);

	for (auto& d : AS->TagsToAttributes)
	{
		BroadcastAttributeInfo(d.Key, d.Value());
	}

	auto AuraPlayerState = CastChecked<AAuraPlayerState>(PlayerState);
	AttributePointsChangedDelegate.Broadcast(AuraPlayerState->GetAttributePoints());
}

void UAttributeMenuWidgetController::UpgradeAttribute(const FGameplayTag& AttributeTag)
{
	auto AuraASC = CastChecked<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	AuraASC->UpgradeAttribute(AttributeTag);
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const
{
	auto Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}
