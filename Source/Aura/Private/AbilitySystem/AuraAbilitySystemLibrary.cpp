// Copyright Huibaekim


#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "UI/HUD/AuraHUD.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "Player/AuraPlayerState.h"
#include "Kismet/GameplayStatics.h"

UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	auto PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	if (nullptr == PC)
	{
		return nullptr;
	}

	auto AuraHUD = Cast<AAuraHUD>(PC->GetHUD());
	if (nullptr == AuraHUD)
	{
		return nullptr;
	}

	auto PS = PC->GetPlayerState<AAuraPlayerState>();
	auto ASC = PS->GetAbilitySystemComponent();
	auto AS = PS->GetAttributeSet();
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	return AuraHUD->GetOverlayWidgetController(WidgetControllerParams);
}

UAttributeMenuWidgetController* UAuraAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	auto PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	if (nullptr == PC)
	{
		return nullptr;
	}

	auto AuraHUD = Cast<AAuraHUD>(PC->GetHUD());
	if (nullptr == AuraHUD)
	{
		return nullptr;
	}

	auto PS = PC->GetPlayerState<AAuraPlayerState>();
	auto ASC = PS->GetAbilitySystemComponent();
	auto AS = PS->GetAttributeSet();
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	return AuraHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
}
