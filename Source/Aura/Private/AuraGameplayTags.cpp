// Copyright Huibaekim


#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

FAuraGameplayTags FAuraGameplayTags::GameplayTags;

void FAuraGameplayTags::InitializeNativeGameplayTags()
{
	GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Strength"));
	GameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Intelligence"));
	GameplayTags.Attributes_Primary_Resilience = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Resilience"));
	GameplayTags.Attributes_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Vigor"));

	GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxHealth"));
	GameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxMana"));
	GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"));
	GameplayTags.Attributes_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ArmorPenetration"));
	GameplayTags.Attributes_Secondary_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.BlockChance"));
	GameplayTags.Attributes_Secondary_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitChance"));
	GameplayTags.Attributes_Secondary_CriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitDamage"));
	GameplayTags.Attributes_Secondary_CriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitResistance"));
	GameplayTags.Attributes_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.HealthRegeneration"));
	GameplayTags.Attributes_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ManaRegeneration"));


	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Input.LMB"));
	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Input.RMB"));
	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Input.1"));
	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Input.2"));
	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Input.3"));
	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Input.4"));
	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Input.Passive.1"));
	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Input.Passive.2"));

	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage"));

	GameplayTags.Damage_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Fire"));
	GameplayTags.Damage_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Lightning"));
	GameplayTags.Damage_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Arcane"));
	GameplayTags.Damage_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Physical"));
	
	GameplayTags.Debuff_Burn = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Burn"));
	GameplayTags.Debuff_Stun = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Stun"));
	GameplayTags.Debuff_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Arcane"));
	GameplayTags.Debuff_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Physical"));

	GameplayTags.Debuff_Chance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Chance"));
	GameplayTags.Debuff_Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Damage"));
	GameplayTags.Debuff_Frequency = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Frequency"));
	GameplayTags.Debuff_Duration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Duration"));
	
	GameplayTags.Attributes_Resistance_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Fire"));
	GameplayTags.Attributes_Resistance_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Lightning"));
	GameplayTags.Attributes_Resistance_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Arcane"));
	GameplayTags.Attributes_Resistance_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Physical"));
	
	GameplayTags.Attributes_Meta_IncomingXP = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Meta.IncomingXP"));

	GameplayTags.Abilities_None = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.None"));

	GameplayTags.Abilities_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Attack"));
	GameplayTags.Abilities_Summon = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Summon"));
	
	GameplayTags.Abilities_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.HitReact"));
	GameplayTags.Abilities_Status_Eligible = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Status.Eligible"));
	GameplayTags.Abilities_Status_Equipped = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Status.Equipped"));
	GameplayTags.Abilities_Status_Locked = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Status.Locked"));
	GameplayTags.Abilities_Status_Unlocked = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Status.Unlocked"));
	
	GameplayTags.Abilities_Type_Offensive = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Type.Offensive"));
	GameplayTags.Abilities_Type_Passive = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Type.Passive"));
	GameplayTags.Abilities_Type_None = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Type.None"));
	
	GameplayTags.Abilities_Fire_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Fire.FireBolt"));
	GameplayTags.Abilities_Lightning_Electrocute = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Lightning.Electrocute"));
	GameplayTags.Abilities_Arcane_ArcaneShards = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Arcane.ArcaneShards"));
	
	GameplayTags.Abilities_Passive_HaloOfProtection = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Passive.HaloOfProtection"));
	GameplayTags.Abilities_Passive_LifeSiphon = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Passive.LifeSiphon"));
	GameplayTags.Abilities_Passive_ManaSiphon = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Passive.ManaSiphon"));
	
	GameplayTags.Cooldown_Fire_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Fire.FireBolt"));

	GameplayTags.CombatSocket_Weapon = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.Weapon"));
	GameplayTags.CombatSocket_LeftHand = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.LeftHand"));
	GameplayTags.CombatSocket_RightHand = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.RightHand"));
	GameplayTags.CombatSocket_Tail = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.Tail"));

	GameplayTags.Montage_Attack_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.1"));
	GameplayTags.Montage_Attack_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.2"));
	GameplayTags.Montage_Attack_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.3"));
	GameplayTags.Montage_Attack_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.4"));

	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Fire, GameplayTags.Attributes_Resistance_Fire);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Lightning, GameplayTags.Attributes_Resistance_Lightning);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Arcane, GameplayTags.Attributes_Resistance_Arcane);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Physical, GameplayTags.Attributes_Resistance_Physical);

	GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Damage_Fire, GameplayTags.Debuff_Burn);
	GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Damage_Lightning, GameplayTags.Debuff_Stun);
	GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Damage_Arcane, GameplayTags.Debuff_Arcane);
	GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Damage_Physical, GameplayTags.Debuff_Physical);
	
	GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Effects.HitReact"));

	GameplayTags.Player_Block_CursorTrace = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Player.Block.CursorTrace"));
	GameplayTags.Player_Block_InputHeld = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Player.Block.InputHeld"));
	GameplayTags.Player_Block_InputPressed = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Player.Block.InputPressed"));
	GameplayTags.Player_Block_InputReleased = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Player.Block.InputReleased"));

}
