/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "Options.h"
#include "../Core/CGenericLogStorage.h"
#include "../Core/FormattedOutput.h"
#include "../Core/LimitAdjuster.h"

#ifdef IS_PLATFORM_WIN_X64
#include <windows.h>
#endif

using namespace Game;

Options g_options;

// Sets the language.
void Options::SetLanguage(const char* language)
{
	MAKE_VAR_GAME_VERSION();

	MAKE_DEAD_IF();
#ifdef IS_PLATFORM_WIN_X64
	else if (CGameVersion::IsAny_GTA_V_WIN_X64(gameVersion))
	{
		HKEY hKey;
		/*
		LONG nError = RegOpenKeyExA(
		HKEY_LOCAL_MACHINE,
		"SOFTWARE\\Wow6432Node\\Rockstar Games\\Grand Theft Auto V",
		NULL,
		KEY_WRITE,
		&hKey
		);
		*/

		LSTATUS result = RegCreateKeyExA(
			HKEY_LOCAL_MACHINE,
			"SOFTWARE\\Wow6432Node\\Rockstar Games\\Grand Theft Auto V",
			NULL,
			NULL,
			REG_OPTION_NON_VOLATILE,
			KEY_WRITE,
			NULL,
			&hKey,
			NULL
		);

		if (result == ERROR_SUCCESS)
		{
			LONG nError = RegSetValueEx(
				hKey,
				"Language",
				NULL,
				REG_SZ,
				(LPBYTE)language,
				strlen(language) + 1
			);

			if (nError == ERROR_SUCCESS)
				CGenericLogStorage::SaveFormattedTextLn("Game language set: %s", language);
			else
			{
				const char* msg = "Cannot set the game language, unable to set the registry value. Try to run game as administrator.";
				CGenericLogStorage::SaveFormattedTextLn(msg);
				printf_MessageBox(msg);
			}				

			CGenericLogStorage::WriteLineSeparator();

			RegCloseKey(hKey);			
		}
		else
			printf_MessageBox("Cannot set the game language, the registry key cannot be opened/created for write access.");
	}
#endif
}