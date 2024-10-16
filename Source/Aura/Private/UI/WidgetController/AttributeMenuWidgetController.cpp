// Copyright Huibaekim


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "AuraGameplayTags.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	auto AS = CastChecked<UAuraAttributeSet>(AttributeSet);

	check(AttributeInfo);

	for (auto& d : AS->TagsToAttributes)
	{
		auto Info = AttributeInfo->FindAttributeInfoForTag(d.Key);
		auto Attr = d.Value.Execute();
		Info.AttributeValue = Attr.GetNumericValue(AttributeSet);
		AttributeInfoDelegate.Broadcast(Info);
	}


}
