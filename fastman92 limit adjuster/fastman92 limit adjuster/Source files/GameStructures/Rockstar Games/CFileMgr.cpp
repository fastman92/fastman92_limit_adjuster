/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CFileMgr.h"
#include "../../Core/LimitAdjuster.h"
#include <stdio.h>

using namespace Game;

CFileMgr_VarInitialisation g_CFileMgr_varInitialization;

static uintptr_t Address_CFileMgr__OpenFile;
static uintptr_t Address_CFileMgr__Read;
static uintptr_t Address_CFileMgr__ReadLine;
static uintptr_t Address_CFileMgr__CloseFile;

char *CFileMgr::ms_dirName = (char *)0xB71A60;
char *CFileMgr::ms_rootDirName = (char *)0xB71AE0;
OSFileDataArea* CFileMgr::fileDataArea = 0;

// functions
void CFileMgr::Initialise()
{
	return g_memoryCall.Function<void>(0x5386F0);
}

int CFileMgr::ChangeDir(const char *path)
{
	return g_memoryCall.Function<int>(0x538730, path);
}

int CFileMgr::SetDir(const char *path)
{
	return g_memoryCall.Function<int>(0x5387D0, path);
}

int CFileMgr::SetDirMyDocuments()
{
	return g_memoryCall.Function<int>(0x538860);
}

int CFileMgr::LoadFile(const char *path, unsigned char *buf, int size, const char *mode)
{
	return g_memoryCall.Function<int>(0x538890, path, buf, size, mode);
}

FILESTREAM CFileMgr::OpenFile(const char *path, const char *mode)
{
	return g_memoryCall.Function<FILESTREAM>(Address_CFileMgr__OpenFile, path, mode);
}

FILESTREAM CFileMgr::OpenFileForWriting(const char *path)
{
	return g_memoryCall.Function<FILESTREAM>(0x538910, path);
}

FILESTREAM CFileMgr::OpenFileForAppending(const char *path)
{
	return g_memoryCall.Function<FILESTREAM>(0x538930, path);
}

int CFileMgr::Read(FILESTREAM file, void *buf, int size)
{
	return g_memoryCall.Function<int>(Address_CFileMgr__Read, file, buf, size);
}

int CFileMgr::Write(FILESTREAM file, const void *buf, int size)
{
	return g_memoryCall.Function<int>(0x538970, file, buf, size);
}

bool CFileMgr::Seek(FILESTREAM file, int offset, int origin)
{
	return g_memoryCall.Function<bool>(0x538990, file, offset, origin);
}

/*
bool CFileMgr::Seek64(FILESTREAM file, __int64 offset, int origin)
{
	return ((int(__cdecl *)(FILE*, int, int))0x538990)((FILE*)file, offset, origin) != 0;

	return fseek((FILE*)file, offset, origin) != 0;

	return _fseeki64((FILE*)file, offset, origin) != 0;
}
*/

bool CFileMgr::ReadLine(FILESTREAM file, char *str, int num)
{
	return g_memoryCall.Function<bool>(Address_CFileMgr__ReadLine, file, str, num);
}

char* CFileMgr::LoadLine(FILESTREAM file)
{
	return g_memoryCall.Function<char*>(0x536F80, file);
}

int CFileMgr::CloseFile(FILESTREAM file)
{
	return g_memoryCall.Function<int>(Address_CFileMgr__CloseFile, file);
}

int CFileMgr::GetFileLength(FILESTREAM file)
{
	return g_memoryCall.Function<int>(0x5389E0, file);
}

int CFileMgr::Tell(FILESTREAM file)
{
	return g_memoryCall.Function<int>(0x538A20, file);
}

bool CFileMgr::GetErrorReadWrite(FILESTREAM file)
{
	return g_memoryCall.Function<bool>(0x538A50, file);
}

static int (*Address_OS_FileRead)(FILESTREAM file, void *buf, int size) = 0;

int Android_CFileMgr_Read(FILESTREAM file, void *buf, int size)
{
	return Address_OS_FileRead(file, buf, size);
}

// Initialize
void CFileMgr_VarInitialisation::Initialise()
{
	if (!g_LimitAdjuster.IsGameVersionSetUpWithMemory())
		return;

	MAKE_VAR_GAME_VERSION();

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (gameVersion == GAME_VERSION_GTA_VC_1_0_WIN_X86)
	{
		Address_CFileMgr__OpenFile = g_mCalc.GetCurrentVAbyPreferedVA(0x48DF90);
		Address_CFileMgr__ReadLine = g_mCalc.GetCurrentVAbyPreferedVA(0x48DEB0);
		Address_CFileMgr__CloseFile = g_mCalc.GetCurrentVAbyPreferedVA(0x48DEA0);
	}
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		Address_CFileMgr__OpenFile = g_mCalc.GetCurrentVAbyPreferedVA(0x538900);
		Address_CFileMgr__Read = g_mCalc.GetCurrentVAbyPreferedVA(0x538950);
		Address_CFileMgr__ReadLine = g_mCalc.GetCurrentVAbyPreferedVA(0x5389B0);
		Address_CFileMgr__CloseFile = g_mCalc.GetCurrentVAbyPreferedVA(0x5389D0);
	}
	else if (CGameVersion::Is_GTA_SA_1_0_1_EU_WIN_X86(gameVersion))
	{
		Address_CFileMgr__OpenFile = g_mCalc.GetCurrentVAbyPreferedVA(0x538DA0);
		Address_CFileMgr__ReadLine = g_mCalc.GetCurrentVAbyPreferedVA(0x538E50);
		Address_CFileMgr__CloseFile = g_mCalc.GetCurrentVAbyPreferedVA(0x538E70);
	}
	#elif defined(IS_PLATFORM_ANDROID)
	else if (true)
	{
		Address_CFileMgr__OpenFile = (uintptr_t)Library::GetSymbolAddress(&g_LimitAdjuster.hModule_of_game, "_ZN8CFileMgr8OpenFileEPKcS1_");
		Address_CFileMgr__Read = (uintptr_t)Android_CFileMgr_Read;
		Address_CFileMgr__ReadLine = (uintptr_t)Library::GetSymbolAddress(&g_LimitAdjuster.hModule_of_game, "_ZN8CFileMgr8ReadLineEjPci");
		Address_CFileMgr__CloseFile = (uintptr_t)Library::GetSymbolAddress(&g_LimitAdjuster.hModule_of_game, "_ZN8CFileMgr9CloseFileEj");

		Address_OS_FileRead = (decltype(Address_OS_FileRead))Library::GetSymbolAddress(&g_LimitAdjuster.hModule_of_game, "_Z11OS_FileReadPvS_i");

		CFileMgr::fileDataArea = (OSFileDataArea*)Library::GetSymbolAddress(&g_LimitAdjuster.hModule_of_game, "_ZN8CFileMgr12fileDataAreaE");
	}
	#endif
}