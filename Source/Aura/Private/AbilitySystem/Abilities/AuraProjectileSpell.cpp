// Copyright Huibaekim


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"
#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Aura/Public/AuraGameplayTags.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UAuraProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation)
{
	const auto bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (false == bIsServer)
	{
		return;
	}

	auto CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (CombatInterface)
	{
		const auto SocketLocation = CombatInterface->GetCombatSocketLocation();
		auto Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
		Rotation.Pitch = 0.f;

		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(Rotation.Quaternion());

		auto Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		auto SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());

		auto SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), SourceASC->MakeEffectContext());
		auto GameplayTags = FAuraGameplayTags::Get();
		const auto ScaledDamage = Damage.GetValueAtLevel(GetAbilityLevel());
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Damage, ScaledDamage);
		Projectile->DamageEffectSpecHandle = SpecHandle;

		Projectile->FinishSpawning(SpawnTransform);
	}
}
