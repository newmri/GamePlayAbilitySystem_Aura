// Copyright Huibaekim


#include "Game/LoadScreenSaveGame.h"

FSavedMap ULoadScreenSaveGame::GetSavedMapWithMapName(const FString& InMapName)
{
	for (const auto& Map : SavedMaps)
	{
		if (Map.MapAssetName == InMapName)
			return Map;
	}

	return FSavedMap();
}

bool ULoadScreenSaveGame::HasMap(const FString& InMapName)
{
	for (const auto& Map : SavedMaps)
	{
		if (Map.MapAssetName == InMapName)
			return true;
	}

	return false;
}
