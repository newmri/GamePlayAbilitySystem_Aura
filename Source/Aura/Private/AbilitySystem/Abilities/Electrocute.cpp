// Copyright Huibaekim


#include "AbilitySystem/Abilities/Electrocute.h"

FString UElectrocute::GetDescription(int32 Level)
{
	const auto ScaledDamage = static_cast<int32>(Damage.GetValueAtLevel(Level));
	const auto ManaCost = FMath::Abs(GetManaCost(Level));
	const auto Cooldown = GetCooldown(Level);

	if (1 == Level)
	{
		return FString::Printf(TEXT(
			"<Title>ELECTROCUTE</>\n\n"
			
			"<Small>Level: </><Level>%d</>\n"
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			"<Default>Emits a beam of lightning "
			"connecting with the target, repeatedly causing </>"
			"<Damage>%d</><Default> lightning damage with"
			" a chance to stun</>"
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
			"<Title>ELECTROCUTE</>\n\n"
					
			"<Small>Level: </><Level>%d</>\n"
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			"<Default>Emits a beam of lightning, "
			"propagating to %d additional targets nearby, causing </>"
			"<Damage>%d</><Default> lightning damage with"
			" a chance to stun</>"
			),
			Level,
			ManaCost,
			Cooldown,
			FMath::Min(Level, MaxNumShockTargets - 1),
			ScaledDamage
			);
	}
}

FString UElectrocute::GetNextLevelDescription(int32 Level)
{
	const auto ScaledDamage =  static_cast<int32>(Damage.GetValueAtLevel(Level));
	const auto ManaCost = FMath::Abs(GetManaCost(Level));
	const auto Cooldown = GetCooldown(Level);

	return FString::Printf(TEXT(
		"<Title>NEXT LEVEL:</>\n\n"
					
		"<Small>Level: </><Level>%d</>\n"
		"<Small>ManaCost: </><ManaCost>%.1f</>\n"
		"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

		"<Default>Emits a beam of lightning, "
		"propagating to %d additional targets nearby, causing </>"
		"<Damage>%d</><Default> lightning damage with"
		" a chance to stun</>"
		),
		Level,
		ManaCost,
		Cooldown,
		FMath::Min(Level, MaxNumShockTargets),
		ScaledDamage
		);
}