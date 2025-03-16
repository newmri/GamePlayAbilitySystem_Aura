// Copyright Huibaekim


#include "AbilitySystem/Abilities/AuraFireBolt.h"

#include "PrimitiveSceneInfo.h"
#include "Aura/Public/AuraGameplayTags.h"
#include "Kismet/KismetSystemLibrary.h"


FString UAuraFireBolt::GetDescription(int32 Level)
{
	const auto ScaledDamage = static_cast<int32>(Damage.GetValueAtLevel(Level));
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
			ScaledDamage
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
			ScaledDamage
			);
	}
}

FString UAuraFireBolt::GetNextLevelDescription(int32 Level)
{
	const auto ScaledDamage =  static_cast<int32>(Damage.GetValueAtLevel(Level));
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
		ScaledDamage
		);
}

void UAuraFireBolt::SpawnProjectiles(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag,
	bool bOverridePitch, float PitchOverride, AActor* HomingTarget)
{
	const auto bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (false == bIsServer)
	{
		return;
	}

	if (auto CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()))
	{
		const auto SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(GetAvatarActorFromActorInfo(), SocketTag);
		auto Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
		if (bOverridePitch)
			Rotation.Pitch = PitchOverride;

		const auto Forward = Rotation.Vector();
		const auto LeftOfSpread = Forward.RotateAngleAxis(-ProjectileSpread / 2.f, FVector::UpVector);
		const auto RightOfSpread = Forward.RotateAngleAxis(ProjectileSpread / 2.f, FVector::UpVector);
		const auto Start = SocketLocation + FVector(0, 0, 5);

		//const int32 NumOfProjectiles = FMath::Min(MaxNumProjectiles, GetAbilityLevel());
		const int32 NumOfProjectiles = NumProjectiles;
		if (NumOfProjectiles > 1)
		{
			const auto DeltaSpread = ProjectileSpread / (NumOfProjectiles - 1);
			for (int32 i = 0; i < NumOfProjectiles; ++i)
			{
				const auto Direction = LeftOfSpread.RotateAngleAxis(i * DeltaSpread, FVector::UpVector);
				UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), Start, Start + Direction * 75.f, 5, FLinearColor::White, 60, 1);
			}
		}
		else
		{
			UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), Start, Start + Forward * 75.f, 5, FLinearColor::White, 60, 1);
		}
	}
}
