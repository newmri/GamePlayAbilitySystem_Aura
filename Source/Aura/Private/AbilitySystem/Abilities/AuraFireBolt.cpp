// Copyright Huibaekim


#include "AbilitySystem/Abilities/AuraFireBolt.h"
#include "Aura/Public/AuraGameplayTags.h"


FString UAuraFireBolt::GetDescription(int32 Level)
{
	const auto Damage = static_cast<int>(GetDamageByDamageType(Level, FAuraGameplayTags::Get().Damage_Fire));
	const auto ManaCost = FMath::Abs(GetManaCost(Level));
	const auto Cooldown = GetCooldown(Level);

	if (1 == Level)
	{
		return FString::Printf(TEXT(
			"<Title>FIRE BOLT</>\n\n"
			
			"<Small>Level: </><Level>%d</>\n"
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			"<Default>Launched a bolt of fire, "
			"exploding on impact and dealing </>"
			"<Damage>%d</><Default> fire damage with"
			" a chance to burn</>"
			),
			Level,
			ManaCost,
			Cooldown,
			Damage
			);
	}
	else
	{
		return FString::Printf(TEXT(
			"<Title>FIRE BOLT</>\n\n"
					
			"<Small>Level: </><Level>%d</>\n"
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			"<Default>Launched %d bolts of fire, "
			"exploding on impact and dealing </>"
			"<Damage>%d</><Default> fire damage with"
			" a chance to burn</>"
			),
			Level,
			ManaCost,
			Cooldown,
			FMath::Min(Level, NumProjectiles),
			Damage
			);
	}
}

FString UAuraFireBolt::GetNextLevelDescription(int32 Level)
{
	const auto Damage = static_cast<int>(GetDamageByDamageType(Level, FAuraGameplayTags::Get().Damage_Fire));
	const auto ManaCost = FMath::Abs(GetManaCost(Level));
	const auto Cooldown = GetCooldown(Level);

	return FString::Printf(TEXT(
		"<Title>NEXT LEVEL</>\n\n"
						
		"<Small>Level: </><Level>%d</>\n"
		"<Small>ManaCost: </><ManaCost>%.1f</>\n"
		"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

		"<Default>Launched %d bolts of fire, "
		"exploding on impact and dealing </>"
		"<Damage>%d</><Default> fire damage with"
		" a chance to burn</>"
		),
		Level,
		ManaCost,
		Cooldown,
		FMath::Min(Level, NumProjectiles),
		Damage
		);
}