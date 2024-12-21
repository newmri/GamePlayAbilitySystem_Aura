// Copyright Huibaekim


#include "AbilitySystem/Data/AbilityInfo.h"

#include "Aura/AuraLogChannels.h"

FAuraAbilityInfo UAbilityInfo::FindAbilityInfoForTag(const FGameplayTag& AbilityTag, bool bLogNotFound) const
{
	
	for (const auto& Info : AbilityInformation)
	{
		if (Info.AbilityTag == AbilityTag)
			return Info;
	}

	if (bLogNotFound)
	{
		UE_LOG(LogAura, Error, TEXT("Ability Tag not found [%s] on AbilityInfo [%s]"), *AbilityTag.ToString(), *GetNameSafe(this));
	}
	
	return FAuraAbilityInfo();
}
