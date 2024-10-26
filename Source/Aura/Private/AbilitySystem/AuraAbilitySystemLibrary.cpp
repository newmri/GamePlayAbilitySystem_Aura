// Copyright Huibaekim


#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "UI/HUD/AuraHUD.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "Player/AuraPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Game/AuraGameModeBase.h"
#include "../../../../Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/AbilitySystemComponent.h"

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

void UAuraAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{
	auto AuraGameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (nullptr == AuraGameMode)
	{
		return;
	}

	auto AvatarActor = ASC->GetAvatarActor();

	auto CharacterClassInfo = AuraGameMode->ChracterClassInfo;
	auto ClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

	auto PrimaryAttributesContextHandle = ASC->MakeEffectContext();
	PrimaryAttributesContextHandle.AddSourceObject(AvatarActor);
	auto PrimaryAttributesSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes, Level, PrimaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data.Get());


	auto SecondaryAttributesContextHandle = ASC->MakeEffectContext();
	SecondaryAttributesContextHandle.AddSourceObject(AvatarActor);
	auto SecondaryAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttributes, Level, SecondaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributesSpecHandle.Data.Get());

	auto VitalAttributesContextHandle = ASC->MakeEffectContext();
	VitalAttributesContextHandle.AddSourceObject(AvatarActor);
	auto VitalAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->VitalAttributes, Level, VitalAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributesSpecHandle.Data.Get());
}
