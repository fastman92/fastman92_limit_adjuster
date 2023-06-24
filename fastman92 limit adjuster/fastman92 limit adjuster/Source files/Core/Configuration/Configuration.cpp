/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "Configuration.h"

#include "../LimitAdjuster.h"

#include <Array/countof.h>

#include "../FormattedOutput.h"

namespace Configuration {

	CGameDescription::CGameDescription()
	{
		this->gameVersion = Game::GAME_VERSION_UNDEFINED;
		this->preferedVA = 0;
		this->humanReadableName = nullptr;
		this->name = nullptr;
		this->appLibIdentifier = nullptr;
		this->numberOfDefinedSizes = 0;
	}
	// Returns count of games in list
	unsigned int tPlatformConfiguration::GetCountOfGamesInList() const
	{
		const CGameDescription* pGameDescription = this->pGameList;
		unsigned int count = 0;

		while (pGameDescription->gameVersion != Game::GAME_VERSION_UNDEFINED)
		{
			pGameDescription++;
			count++;
		}

		return count;
	}

	struct tDocumentationWorkbook;

	static // Check if a char array contains a character
		bool startWith(
			const char * arr,
			const char* substring)
	{
		bool result = false;
		// get number of characters in substring
		size_t subStrLen = strlen(substring);
		// get number of characters in char array string
		size_t mainStrLen = strlen(arr);
		// Check if char array starts with the given substring
		if (mainStrLen >= subStrLen &&
			strncmp(arr, substring, subStrLen) == 0)
		{
			result = true;
		}
		return result;
	}

	// Returns text description about platform
	std::string tPlatformConfiguration::GetTextDescriptionAboutGames(bool bExtendedInfo) const
	{
		std::string result;
		char str[256];

		enum
		{
			PLATFORM_TYPE_WIN,
			PLATFORM_TYPE_ANDROID
		} platformType;

		if (startWith(this->solutionPlatformName, "WIN_"))
			platformType = PLATFORM_TYPE_WIN;
		else if (startWith(this->solutionPlatformName, "ANDROID_"))
			platformType = PLATFORM_TYPE_ANDROID;

		const CGameDescription* pGameDescription = this->pGameList;

		unsigned int i = 1;

		while (pGameDescription->gameVersion != Game::GAME_VERSION_UNDEFINED)
		{
			sprintf(str,
				"\n%d. %s:\n",
				i, pGameDescription->humanReadableName
			);

			result += str;

			if (platformType == PLATFORM_TYPE_WIN)
			{
				if (pGameDescription->numberOfDefinedSizes)
					for (unsigned j = 0; j < pGameDescription->numberOfDefinedSizes; j++)
					{
						sprintf(str, "\tEXE size:  %d bytes\n", pGameDescription->sizeArray[j]);
						result += str;
					}
				else
					result += "\tEXE size:  does not matter\n";

			}
			else if (platformType == PLATFORM_TYPE_ANDROID)
			{
				sprintf(str,
					"\tSO library identifier: \"%s|%s\"\n",
					pGameDescription->appLibIdentifier,
					this->platformABI);

				result += str;
			}

			{
				const char* INIfilename = CLimitAdjuster::GetIniFilenameForGame(pGameDescription->gameVersion, false);

				if (INIfilename)
				{
					sprintf(str, "\twill use %s\n", INIfilename);
					result += str;
				}
			}

			pGameDescription++;
			i++;
		}

		return result;
	}
	

	// Inits a structure
	void CConfigurationField::Init()
	{
		this->valueType = CONFIGURATION_FIELD_VALUE_TYPE_UNDEFINED;

		this->INIstate = INI_FIELD_NONE;
		this->ExcelState = EXCEL_FIELD_STATE_EMPTY;
		this->bIsOneValuePerPlatform = false;

		this->comment[0] = 0;

		this->INIkeyName[0] = 0;
	}

	// Sets a value of type str
	void CConfigurationField::SetStrValue(const char* Value, eIniFieldState INIstate, eExcelFieldState XLSXstate)
	{
		this->valueType = CONFIGURATION_FIELD_VALUE_TYPE_STRING;
		strncpy(this->value.Str, Value, sizeof(this->value.Str));

		this->INIstate = INIstate;
		this->ExcelState = XLSXstate;
	}

	// Sets a value of type int
	void CConfigurationField::SetIntValue(int64_t Value, eIniFieldState INIstate, eExcelFieldState XLSXstate)
	{
		this->valueType = CONFIGURATION_FIELD_VALUE_TYPE_INT;
		this->value.Int = Value;

		this->INIstate = INIstate;
		this->ExcelState = XLSXstate;
	}

	// Sets a value of type double
	void CConfigurationField::SetDoubleValue(double Value, eIniFieldState INIstate, eExcelFieldState XLSXstate)
	{
		this->valueType = CONFIGURATION_FIELD_VALUE_TYPE_DOUBLE;
		this->value.Double = Value;

		this->INIstate = INIstate;
		this->ExcelState = XLSXstate;
	}

	// Sets a comment
	void CConfigurationField::SetComment(const char* comment)
	{
		strcpy(this->comment, comment);
	}

	// Sets INI key name
	void CConfigurationField::SetINIkeyName(const char* key)
	{
		strcpy(this->INIkeyName, key);
	}

	// Gets value to string
	bool CConfigurationField::ValueToStr(char* str)
	{
		if (this->valueType == CONFIGURATION_FIELD_VALUE_TYPE_INT)
			sprintf(str, "%lld", this->value.Int);
		else if (this->valueType == CONFIGURATION_FIELD_VALUE_TYPE_DOUBLE)
		{
			if ((int)this->value.Double == this->value.Double)
				sprintf(str, "%g.0", this->value.Double);
			else
				sprintf(str, "%g", this->value.Double);
		}
		else if (this->valueType == CONFIGURATION_FIELD_VALUE_TYPE_STRING)
			strcpy(str, this->value.Str);
		else
		{
			*str = 0;
			return false;
		}

		return true;
	}

	///////////////////////////////////////
	// Initialises documentation workbook
	void Workbook::InitializeDocumentationWorkbook(
		CLimitAdjuster* pLimitAdjuster,
		tDocumentationWorkbook* pWorkbook,
		const tPlatformConfiguration* platformList,
		const tConfigurationSection* ConfigurationSectionArray
	)
	{
		using namespace Game;

		pWorkbook->pLimitAdjuster = pLimitAdjuster;

		// Local variable
		CConfigurationField field;

		// Count the number of platforms
		unsigned int countOfPlatforms = 0;

		{
			const tPlatformConfiguration* pPlatform = platformList;

			while (pPlatform->solutionPlatformName)
			{
				countOfPlatforms++;
				pPlatform++;
			}
		}

		// Set up the platforms
		pWorkbook->pPlatformList = platformList;
		pWorkbook->countOfPlatforms = countOfPlatforms;

		// Count the number of all games
		pWorkbook->numberOfAllGamesInAllPlatforms = 0;

		for (int i = 0; i < countOfPlatforms; i++)
		{
			const tPlatformConfiguration* pPlatformConfiguration = platformList + i;
			const CGameDescription* pGameVersionDescription = pPlatformConfiguration->pGameList;
			
			if(pGameVersionDescription->gameVersion == GAME_VERSION_UNDEFINED)
				pWorkbook->numberOfAllGamesInAllPlatforms++;
			else
			{
				while (pGameVersionDescription->gameVersion != GAME_VERSION_UNDEFINED)
				{
					pWorkbook->numberOfAllGamesInAllPlatforms++;
					pGameVersionDescription++;
				}
			};
		}

		pWorkbook->gamesInAllPlatforms = new const Configuration::CGameDescription*[pWorkbook->numberOfAllGamesInAllPlatforms];

		// Set up sections
		pWorkbook->numberOfSections = 0;

		const tConfigurationSection* pSection = ConfigurationSectionArray;

		while (pSection->sectionName)
		{
			pSection++;
			pWorkbook->numberOfSections++;
		}

		pWorkbook->pSectionArray = new tConfigurationSectionProcessed[pWorkbook->numberOfSections];

		for (unsigned sectionID = 0; sectionID < pWorkbook->numberOfSections; sectionID++)
		{
			tConfigurationSectionProcessed* pSectionProcessed = pWorkbook->pSectionArray + sectionID;
			pSection = ConfigurationSectionArray + sectionID;

			// Initialize count of entries
			pSectionProcessed->countOfEntries = 0;

			// Section name
			strncpy(
				pSectionProcessed->sectionName,
				pSection->sectionName,
				sizeof(pSectionProcessed->sectionName)
			);

			// Iterate over fields
			const tConfigurationSectionEntry* pFieldDescriptor = pSection->pFieldDescriptorArray;

			// Figure out the count of entries
			while (pFieldDescriptor->pFunc)
			{
				pSectionProcessed->countOfEntries++;
				pFieldDescriptor++;
			}

			// Set the fields
			pSectionProcessed->pEntryArray = new tConfigurationSectionEntryProcessed[pSectionProcessed->countOfEntries];

			for (unsigned int sectionEntryID = 0;
				sectionEntryID < pSectionProcessed->countOfEntries;
				sectionEntryID++)
			{
				tConfigurationSectionEntryProcessed* pSectionEntryProcessed = pSectionProcessed->pEntryArray + sectionEntryID;
				pFieldDescriptor = pSection->pFieldDescriptorArray + sectionEntryID;

				// Key name
				strncpy(
					pSectionEntryProcessed->key,
					pFieldDescriptor->key,
					sizeof(pSectionEntryProcessed->key)
				);

				// Comment
				pFieldDescriptor->pFunc(&field, FIELD_PROCESS_MODE_EXCEL);
				strncpy(pSectionEntryProcessed->comment, field.comment, sizeof(pSectionEntryProcessed->comment));

				// Allocate the fields
				pSectionEntryProcessed->pEntryArray = new CConfigurationField[pWorkbook->numberOfAllGamesInAllPlatforms];
			}
		}

		// Set the fields for each game. Set the values.
		unsigned gameColumn = 0;

		for (int i = 0; i < countOfPlatforms; i++)
		{
			const tPlatformConfiguration* pPlatformConfiguration = platformList + i;
			pLimitAdjuster->pPlatformConfig = pPlatformConfiguration;

			const CGameDescription* pGameVersionDescription = pPlatformConfiguration->pGameList;

			// Is empty platform game list?
			if (pGameVersionDescription->gameVersion == GAME_VERSION_UNDEFINED)
				gameColumn++;
			else
				while (pGameVersionDescription->gameVersion != GAME_VERSION_UNDEFINED)
				{
					pWorkbook->gamesInAllPlatforms[gameColumn] = pGameVersionDescription;

					eGameVersion game = pGameVersionDescription->gameVersion;
					pLimitAdjuster->SetGameInfo(0, 0, game, "N/A");

					// Initialize the modules
					pLimitAdjuster->InitializeModules();

					// Iterate the sections
					for (unsigned sectionID = 0; sectionID < pWorkbook->numberOfSections; sectionID++)
					{
						tConfigurationSectionProcessed* pSectionProcessed = pWorkbook->pSectionArray + sectionID;
						pSection = ConfigurationSectionArray + sectionID;

						// Iterate over entries
						for (unsigned int sectionEntryID = 0;
							sectionEntryID < pSectionProcessed->countOfEntries;
							sectionEntryID++)
						{
							const tConfigurationSectionEntry* pSectionEntryDescriptor = pSection->pFieldDescriptorArray + sectionEntryID;
							tConfigurationSectionEntryProcessed* pSectionEntry = pSectionProcessed->pEntryArray + sectionEntryID;

							pSectionEntryDescriptor->pFunc(
								pSectionEntry->pEntryArray + gameColumn,
								FIELD_PROCESS_MODE_EXCEL
							);
						}
					}

					// Shutdown the modules
					pLimitAdjuster->ShutDownModules();

					pGameVersionDescription++;
					gameColumn++;
				}
		}

		// Count of features
		tConfigurationSectionProcessed* pNoNameSection = std::find_if(pWorkbook->pSectionArray, pWorkbook->pSectionArray + pWorkbook->numberOfSections,
			[](const tConfigurationSectionProcessed& pSection)
		{
			return !pSection.sectionName[0];
		});

		if (pNoNameSection)
		{
			tConfigurationSectionEntryProcessed* pSectionEntryCountOfFeatures = std::find_if(pNoNameSection->pEntryArray, pNoNameSection->pEntryArray + pNoNameSection->countOfEntries,
				[](const tConfigurationSectionEntryProcessed& pSectionEntry)
			{

				return !strcmp(pSectionEntry.key, "Count of supported features");
			});

			if (pSectionEntryCountOfFeatures)
			{
				// Iterate over games
				for (unsigned int gameID = 0; gameID < pWorkbook->numberOfAllGamesInAllPlatforms; gameID++)
				{
					unsigned int countOfFeaturesPerGame = 0;

					// Iterate the sections
					for (unsigned sectionID = 0; sectionID < pWorkbook->numberOfSections; sectionID++)
					{
						const tConfigurationSectionProcessed* pSectionProcessed = pWorkbook->pSectionArray + sectionID;

						if (pSectionProcessed == pNoNameSection)	// skip no name section, when counting
							continue;

						// Iterate over entries
						for (unsigned int sectionEntryID = 0;
							sectionEntryID < pSectionProcessed->countOfEntries;
							sectionEntryID++)
						{
							const tConfigurationSectionEntryProcessed* pSectionEntry = pSectionProcessed->pEntryArray + sectionEntryID;

							const CConfigurationField* pField = &pSectionEntry->pEntryArray[gameID];

							if (pField->INIstate == INI_FIELD_ACTIVE || pField->INIstate == INI_FIELD_INACTIVE)
								countOfFeaturesPerGame++;
						}
					}

					// Set count of supported features for this game
					pSectionEntryCountOfFeatures->pEntryArray[gameID].SetIntValue(countOfFeaturesPerGame, INI_FIELD_NONE, EXCEL_FIELD_STATE_SUPPORTED_ONLY_SHOW_VALUE);
				}
			}

			
		}
	}

	// Clear documentation workbook, deallocates the data
	void Workbook::ClearDocumentationWorkbook(tDocumentationWorkbook* pWorkbook)
	{
		delete[] pWorkbook->gamesInAllPlatforms;

		for (unsigned sectionID = 0; sectionID < pWorkbook->numberOfSections; sectionID++)
		{
			tConfigurationSectionProcessed* pSection = pWorkbook->pSectionArray + sectionID;

			for (unsigned int sectionEntryID = 0;
				sectionEntryID < pSection->countOfEntries;
				sectionEntryID++)
			{
				tConfigurationSectionEntryProcessed* pSectionEntry = pSection->pEntryArray + sectionEntryID;
				delete[] pSectionEntry->pEntryArray;
			}

			delete[] pSection->pEntryArray;
		}

		delete[] pWorkbook->pSectionArray;
	}
}