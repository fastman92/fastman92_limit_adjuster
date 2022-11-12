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

	// Inits a structure
	void CConfigurationField::Init()
	{
		this->valueType = CONFIGURATION_FIELD_VALUE_TYPE_UNDEFINED;

		this->INIstate = INI_FIELD_NONE;
		this->ExcelState = EXCEL_FIELD_STATE_EMPTY;

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

			while (pPlatform->platformName)
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
			const eGameVersion* pGameVersion = pPlatformConfiguration->pGameList;
			
			if(*pGameVersion == GAME_VERSION_UNDEFINED)
				pWorkbook->numberOfAllGamesInAllPlatforms++;
			else
			{
				while (*pGameVersion != GAME_VERSION_UNDEFINED)
				{
					pWorkbook->numberOfAllGamesInAllPlatforms++;
					pGameVersion++;
				}
			};
		}

		pWorkbook->gameNamesInAllPlatforms = new const char*[pWorkbook->numberOfAllGamesInAllPlatforms];

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
			const eGameVersion* pGameVersion = pPlatformConfiguration->pGameList;

			// Is empty platform game list?
			if (*pGameVersion == GAME_VERSION_UNDEFINED)
				gameColumn++;
			else
				while (*pGameVersion != GAME_VERSION_UNDEFINED)
				{
					eGameVersion game = *pGameVersion;
					pLimitAdjuster->SetGameInfo(0, 0, game, "N/A");

					const char* gameVersionName = CGameVersion::GetGameNameByMemberWithoutPlatformName(game);
					pWorkbook->gameNamesInAllPlatforms[gameColumn] = gameVersionName;

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

					pGameVersion++;
					gameColumn++;
				}
		}
	}

	// Clear documentation workbook, deallocates the data
	void Workbook::ClearDocumentationWorkbook(tDocumentationWorkbook* pWorkbook)
	{
		delete[] pWorkbook->gameNamesInAllPlatforms;

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