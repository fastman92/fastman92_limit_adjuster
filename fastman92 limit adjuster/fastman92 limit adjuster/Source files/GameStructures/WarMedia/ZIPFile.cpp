#include "ZIPFile.h"

#include "../../Core/LimitAdjuster.h"

ZIPFile_VarInitialisation g_ZIPFile_VarInitialisation;

static uintptr_t Address_ZIPFile__OpenFromStorage = 0;

// Opens file from storage
OSFile ZIPFile::OpenFromStorage(const char *filename, OSFileAccessType access)
{
	return g_memoryCall.Function<OSFile>(Address_ZIPFile__OpenFromStorage, filename, access);
}

static uintptr_t Address_ZIPFile__FindFromStorage = 0;

// Finds a file
int ZIPFile::FindFromStorage(const char *filename, ZIPFile **inZip)
{
	return g_memoryCall.Function<int>(Address_ZIPFile__FindFromStorage, filename, inZip);
}

// Initialize
void ZIPFile_VarInitialisation::Initialise()
{
	MAKE_VAR_GAME_VERSION();

	MAKE_DEAD_IF();
#ifdef IS_PLATFORM_ANDROID
	Address_ZIPFile__OpenFromStorage = (uintptr_t)Library::GetSymbolAddress(&g_LimitAdjuster.hModule_of_game, "_ZN7ZIPFile15OpenFromStorageEPKc16OSFileAccessType");
	Address_ZIPFile__FindFromStorage = (uintptr_t)Library::GetSymbolAddress(&g_LimitAdjuster.hModule_of_game, "_ZN7ZIPFile15FindFromStorageEPKcPPS_");
#endif
}