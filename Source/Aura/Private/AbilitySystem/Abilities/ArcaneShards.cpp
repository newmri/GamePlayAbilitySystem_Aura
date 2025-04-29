// Copyright Huibaekim


#include "AbilitySystem/Abilities/ArcaneShards.h"

FString UArcaneShards::GetDescription(int32 Level)
{
	const auto ScaledDamage = static_cast<int32>(Damage.GetValueAtLevel(Level));
	const auto ManaCost = FMath::Abs(GetManaCost(Level));
	const auto Cooldown = GetCooldown(Level);

	if (1 == Level)
	{
		return FString::Printf(TEXT(
			"<Title>ARCANE SHARDS</>\n\n"
			
			"<Small>Level: </><Level>%d</>\n"
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			"<Default>Summon shards of arcane energy, "
			"causing radial arcane damage of </>"
			"<Damage>%d</><Default> at the shard origin."
			"</>"
			),
			Level,
			ManaCost,
			Cooldown,
			ScaledDamage
			);
	}
	else
	{
		return FString::Printf(TEXT(
			"<Title>ARCANE SHARDS</>\n\n"
					
			"<Small>Level: </><Level>%d</>\n"
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			"<Default>Summon shards of arcane energy, "
			"causing radial arcane damage of </>"
			"<Damage>%d</><Default> at the shard origin."
			"</>"
			),
			Level,
			ManaCost,
			Cooldown,
			ScaledDamage
			);
	}
}

FString UArcaneShards::GetNextLevelDescription(int32 Level)
{
	const auto ScaledDamage =  static_cast<int32>(Damage.GetValueAtLevel(Level));
	const auto ManaCost = FMath::Abs(GetManaCost(Level));
	const auto Cooldown = GetCooldown(Level);

	return FString::Printf(TEXT(
		"<Title>NEXT LEVEL:</>\n\n"
					
		"<Small>Level: </><Level>%d</>\n"
		"<Small>ManaCost: </><ManaCost>%.1f</>\n"
		"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

		"<Default>Summon %d shards of arcane energy, "
		"causing radial arcane damage of </>"
		"<Damage>%d</><Default> at the shard origin."
		"</>"
		),
		Level,
		ManaCost,
		Cooldown,
		FMath::Min(Level, MaxNumShards),
		ScaledDamage
		);
}
