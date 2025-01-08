// Copyright Huibaekim


#include "AbilitySystem/Data/LevelUpInfo.h"

int32 ULevelUpInfo::FindLevelForXP(int32 XP)
{
	if (0 == LevelUpInfo.Num())
		return 1;
	
	int32 Level = 0;
	bool bSearching = true;
	while (bSearching)
	{
		if (XP >= LevelUpInfo[Level].LevelUpRequirement)
			++Level;
		else
			bSearching = false;
	}

	return ++Level;
}
