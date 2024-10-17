// Copyright Huibaekim


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	auto AS = CastChecked<UAuraAttributeSet>(AttributeSet);

	for (auto& d : AS->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(d.Value()).AddLambda(
			[this, d](const FOnAttributeChangeData& Data)
			{
				BroadcastAttributgeInfo(d.Key, d.Value());
			}
		);
	}
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	auto AS = CastChecked<UAuraAttributeSet>(AttributeSet);

	check(AttributeInfo);

	for (auto& d : AS->TagsToAttributes)
	{
		BroadcastAttributgeInfo(d.Key, d.Value());
	}
}

void UAttributeMenuWidgetController::BroadcastAttributgeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const
{
	auto Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}
