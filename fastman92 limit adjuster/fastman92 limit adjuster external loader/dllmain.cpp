/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

// dllmain.cpp : Defines the entry point for the DLL application.

#ifdef IS_PLATFORM_WIN
#include <windows.h>
#include <stdio.h>

#if !defined(STRINGIFY) || defined(TOSTRING)
#define STRINGIFY(str) #str
#define TOSTRING(x) STRINGIFY(x)
#endif

enum eVersionToRun
{
	VERSION_TO_RUN_NONE,
	VERSION_TO_RUN_DEBUG,
	VERSION_TO_RUN_RELEASE
};

HMODULE FLA_module = NULL;

void printf_MessageBox(const wchar_t * format, ...)
{
#ifdef IS_PLATFORM_WIN
	va_list vl;
	va_start(vl, format);

	wchar_t buffer[4096];

	_vsnwprintf_s(buffer, _countof(buffer), _countof(buffer) - 1, format, vl);
	MessageBoxW(NULL, buffer, L"fastman92 limit adjuster external loader", MB_OK);
	va_end(vl);
#endif
}

void LoadTheFLA()
{
	wchar_t FLA_DEV_path[MAX_PATH];

	DWORD result = GetEnvironmentVariableW(
		L"FASTMAN92_LIMIT_ADJUSTER_DEVELOPMENT_PATH",
		FLA_DEV_path,
		_countof(FLA_DEV_path)
	);

	if (result == 0)
	{
		printf_MessageBox(L"Failed to retrieve FASTMAN92_LIMIT_ADJUSTER_DEVELOPMENT_PATH. The FLA will not be started.");
		return;
	}

	wchar_t FLA_release_directory[MAX_PATH];

	result = GetEnvironmentVariableW(L"FASTMAN92_LIMIT_ADJUSTER_RELEASE_DIRECTORY",
		FLA_release_directory,
		_countof(FLA_release_directory)
	);

	if (result == 0)
	{
		printf_MessageBox(L"Failed to retrieve FASTMAN92_LIMIT_ADJUSTER_RELEASE_DIRECTORY. The FLA will not be started.");
		return;
	}

	wchar_t FLAlibraryPath[MAX_PATH];
	wchar_t FLAreleasePluginPath[MAX_PATH];	 // the directory with other DLL files

	const wchar_t* Configuration = nullptr;

	wchar_t ConfigFilePath[MAX_PATH];

	swprintf(
		ConfigFilePath,
		L"%ls\\LoadSettings\\VersionToRun.txt",
		FLA_DEV_path
	);

	{
		FILE* fp = _wfopen(ConfigFilePath, L"r");

		if (!fp)
		{
			printf_MessageBox(L"Unable to read %ls", ConfigFilePath);

			// Close the process
			ExitProcess(NULL);
		}

		char num_line[32];
		fgets(num_line, sizeof(num_line), fp);
		fclose(fp);

		eVersionToRun versionToRun = (eVersionToRun)atoi(num_line);

		if (versionToRun == VERSION_TO_RUN_NONE)
			return;
		else if (versionToRun == VERSION_TO_RUN_DEBUG)
			Configuration = L"Debug";
		else if(versionToRun == VERSION_TO_RUN_RELEASE)
			Configuration = L"Release";
		else
		{
			printf_MessageBox(L"File %ls, wrong version to run: %d", ConfigFilePath, versionToRun);

			// Close the process
			ExitProcess(NULL);
		}
	}

	const char* FLAfilename = nullptr;
	const char* solutionPlatform = TOSTRING(SOLUTION_PLATFORM);

	FLAfilename = "$fastman92limitAdjuster.asi";

	swprintf(
		FLAlibraryPath,
		L"%ls\\fastman92 limit adjuster\\Output\\%ls\\%hs\\%hs",
		FLA_DEV_path,
		Configuration,
		solutionPlatform,
		FLAfilename
	);
	
	swprintf(
		FLAreleasePluginPath,
		L"%ls\\files\\files\\libraries\\%hs",
		FLA_release_directory,
		solutionPlatform
	);

	SetDllDirectoryW(FLAreleasePluginPath);

	FLA_module = LoadLibraryW(FLAlibraryPath);

	if (!FLA_module)
	{
		printf_MessageBox(
			L"Unable to load the FLA.\nFLA release directory plugin path: %ls\nFLA ASI path: %ls",
			FLAreleasePluginPath,
			FLAlibraryPath
		);

		// Close the process
		ExitProcess(NULL);
	}
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		LoadTheFLA();
		break;
	}
	case DLL_PROCESS_DETACH:
		if (FLA_module)
			FreeLibrary(FLA_module);
		break;
	}
	return TRUE;
}
#endif