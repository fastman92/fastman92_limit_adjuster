/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once

#include "../eGameVersion.h"

class CLimitAdjuster;

namespace Configuration
{
	enum eFieldProcessMode
	{
		FIELD_PROCESS_MODE_UNDEFINED,

		FIELD_PROCESS_MODE_EXCEL,
		FIELD_PROCESS_MODE_INI_FILE,
	};

	enum eConfigurationFieldValueType {
		CONFIGURATION_FIELD_VALUE_TYPE_UNDEFINED,
		CONFIGURATION_FIELD_VALUE_TYPE_INT,
		CONFIGURATION_FIELD_VALUE_TYPE_DOUBLE,
		CONFIGURATION_FIELD_VALUE_TYPE_STRING,
	};

	enum eIniFieldState
	{
		INI_FIELD_NONE,	// not in the .ini
		INI_FIELD_ACTIVE,	// in the .ini, but commented out
		INI_FIELD_INACTIVE		// in the .ini, active
	};

	enum eExcelFieldState
	{
		EXCEL_FIELD_STATE_EMPTY,	// not in XLSX

		EXCEL_FIELD_STATE_NOT_SUPPORTED,	// say not supported and show value
		EXCEL_FIELD_STATE_NOT_SUPPORTED_ONLY_SHOW_VALUE,	// it's supported, but only show value

		EXCEL_FIELD_STATE_SUPPORTED,	// say supported and show value
		EXCEL_FIELD_STATE_SUPPORTED_ONLY_SHOW_VALUE	// it's supported, but only show value
	};

#define CONFIGURATION_FIELD_MAX_COMMENT_LENGTH 1023

	class CConfigurationField
	{
	public:
		char comment[CONFIGURATION_FIELD_MAX_COMMENT_LENGTH + 1];

		eConfigurationFieldValueType valueType;

		eIniFieldState INIstate;
		eExcelFieldState ExcelState;

		// set for few fields only. Other than that it should contain an empty string
		char INIkeyName[128];

		union
		{
			int64_t Int;
			double Double;
			char Str[256];
		} value;

		// Inits a structure
		void Init();

		// Sets a value of type str
		void SetStrValue(const char* Value, eIniFieldState INIstate, eExcelFieldState XLSXstate);

		// Sets a value of type int
		void SetIntValue(int64_t Value, eIniFieldState INIstate, eExcelFieldState XLSXstate);

		// Sets a value of type double
		void SetDoubleValue(double Value, eIniFieldState INIstate, eExcelFieldState XLSXstate);

		// Sets a comment
		void SetComment(const char* comment);

		// Sets INI key name
		void SetINIkeyName(const char* key);

		// Gets value to string
		bool ValueToStr(char* str);
	};

	struct tPlatformConfiguration
	{
		const char* platformName;
		const Game::eGameVersion* pGameList;
	};

#define PLATFORM_CONFIGURATION_EOF { nullptr, nullptr }

	typedef void(*tProcessFieldFunc)(CConfigurationField* pField, eFieldProcessMode fieldProcessMode);

	struct tConfigurationSectionEntry
	{
		const char* key;
		tProcessFieldFunc pFunc;
	};

#define BEGIN_FIELD_FUNCTION [](CConfigurationField* pField, eFieldProcessMode fieldProcessMode) \
{ \
	MAKE_VAR_GAME_VERSION(); \
	pField->Init();

#define END_FIELD_FUNCTION	} \

	///////

#define SECTION_FIELD_EOF { nullptr, nullptr }

	struct tConfigurationSection
	{
		const char* sectionName;
		const tConfigurationSectionEntry* pFieldDescriptorArray;
	};

///////////////////////////
	struct tConfigurationSectionEntryProcessed
	{
		// Field name
		char key[64];

		// Field comment
		char comment[CONFIGURATION_FIELD_MAX_COMMENT_LENGTH + 1];

		// an array with entries per each game
		CConfigurationField* pEntryArray;
	};

	// Configuration section, processed
	struct tConfigurationSectionProcessed
	{
		// Name of section
		char sectionName[64];

		// Entries in section
		tConfigurationSectionEntryProcessed* pEntryArray;
		unsigned int countOfEntries;
	};

	// Documentation workbook
	struct tDocumentationWorkbook
	{
		CLimitAdjuster* pLimitAdjuster;

		const tPlatformConfiguration* pPlatformList;
		unsigned countOfPlatforms;

		const char** gameNamesInAllPlatforms;
		unsigned int numberOfAllGamesInAllPlatforms;

		tConfigurationSectionProcessed* pSectionArray;
		unsigned int numberOfSections;
	};

	// functions to set up the workbook and delete it
	class Workbook
	{
	public:
		// Initialises documentation workbook
		static void InitializeDocumentationWorkbook(
			CLimitAdjuster* pLimitAdjuster,
			tDocumentationWorkbook* pWorkbook,
			const tPlatformConfiguration* platformList,
			const tConfigurationSection* ConfigurationSectionArray
		);

		// Clear documentation workbook, deallocates the data
		static void ClearDocumentationWorkbook(tDocumentationWorkbook* pWorkbook);
	};
}