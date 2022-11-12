/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "ModelSpecialFeatures.h"

#include "FileIDlimit.h"

#include "../Core/CGenericLogStorage.h"
#include "../Core/FormattedOutput.h"
#include "../Core/LimitAdjuster.h"

#include <fileIO.h>
#include <IMG\IMGstructures.h>
#include <StrLexStuff.h>

using namespace Game;

ModelSpecialFeatures g_modelSpecialFeatures;

int32_t GetModelIDforModelSpecialFeaturesNoChanges(int32_t modelID)
{
	return modelID;
}

int32_t GetModelIDforModelSpecialFeaturesWithChanges(int32_t modelID)
{
	return g_modelSpecialFeatures.GetStandardModelIDbyCustomModelID(modelID);
}

int32_t(__cdecl* GetModelIDforModelSpecialFeatures)(int32_t modelID) = GetModelIDforModelSpecialFeaturesNoChanges;

// Initialize
void ModelSpecialFeatures::Initialise()
{
	this->bSpecialFeaturesEnabled = false;
}

// Shutdown
void ModelSpecialFeatures::Shutdown()
{
	this->mapOfIds.clear();
}

// Enables special features
void ModelSpecialFeatures::EnableSpecialFeatures(bool bEnableSpecialFeatures)
{
	if (bEnableSpecialFeatures
		&& !PROJECT_USE_DEVELOPMENT_INI
		&& !g_fileIDlimits.IsIDlimitsPatchEnabled())
		throw f92_runtime_error(
			"Enabled feature ([ADDONS] -> Enable model special feature loader) requires the patch of ID limits enabled.\n"
			"Please change ([ID LIMITS] -> Apply ID limit patch) appropriately."
		);

	this->bSpecialFeaturesEnabled = bEnableSpecialFeatures;
}

// Returns true if special features are enabled
bool ModelSpecialFeatures::AreSpecialFeaturesEnabled()
{
	return this->bSpecialFeaturesEnabled;
}

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTASA
{
	NAKED void patch_CFileLoader__LoadLevel_5B9321()
	{
		__asm
		{
			mov ecx, ASM_GET_OFFSET_OF_FLA_MODULE(g_modelSpecialFeatures);
			call ModelSpecialFeatures::LoadConfiguration;

			mov eax, 0x410E00;	// CColStore::RemoveAllCollision
			jmp eax;
		}
	}
}
#endif

// Applies special features loader
void ModelSpecialFeatures::ApplyLoader()
{
	if (!this->bSpecialFeaturesEnabled)
		return;

	MAKE_VAR_GAME_VERSION();
	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;

		CPatch::RedirectCode(0x5B9321, &patch_CFileLoader__LoadLevel_5B9321);
	}
	#endif
	else
		return;

	CGenericLogStorage::SaveTextLn(
		"Model special features loader enabled."
	);

	CGenericLogStorage::WriteLineSeparator();
}

// Returns standard model ID by custom model ID
INLINE int32_t ModelSpecialFeatures::GetStandardModelIDbyCustomModelID(int32_t modelID)
{
	auto it = this->mapOfIds.find(modelID);

	if (it != this->mapOfIds.end())
		return it->second;
	else
		return modelID;
}

// Returns model ID by name
bool ModelSpecialFeatures::GetModelID(const char* modelName, int* pModelID)
{
	CBaseModelInfo_generic* pModelInfo = CModelInfo::GetModelInfo(modelName, pModelID);

	if (pModelInfo)
		return true;
	else
	{
		printf_MessageBox("Model special features loader: model with name %s does not exist.", modelName);
		return false;
	}
}

// Loads configuration
void ModelSpecialFeatures::LoadConfiguration()
{
	this->mapOfIds.clear();
	const char* filename = g_LimitAdjuster.GetPathToFlaFileFromRootDirectory("data\\model_special_features.dat").c_str();

	FILE* fp = fopen(filename, "r");

	if (!fp)
	{
		printf_MessageBox("Unable to load %s", filename);
		g_LimitAdjuster.TerminateProcess();
	}

	char line[1024];
	char customModelName[IMG_FASTMAN92_GTASA_MAX_FILENAME_LENGTH];
	char standardModelName[IMG_FASTMAN92_GTASA_MAX_FILENAME_LENGTH];

	while (LoadLineWithoutCommas(line, sizeof(line), fp))
	{
		char* iLine = FindFirstNonWhiteCharacter(line);

		if (!iLine[0] || iLine[0] == '#')
			continue;

		sscanf(
			line,
			"%s %s",
			customModelName,
			standardModelName
		);

		int customModelID;
		int standardModelID;

		if (this->GetModelID(standardModelName, &standardModelID)
			&& this->GetModelID(customModelName, &customModelID))
			this->mapOfIds[customModelID] = standardModelID;
	}

	fclose(fp);

	if (this->mapOfIds.empty())
		GetModelIDforModelSpecialFeatures = GetModelIDforModelSpecialFeaturesNoChanges;
	else
		GetModelIDforModelSpecialFeatures = GetModelIDforModelSpecialFeaturesWithChanges;
}