#include "ZIP.h"

#include "../../Core/LimitAdjuster.h"

ZIP_VarInitialisation g_ZIP_VarInitialisation;

static uintptr_t Address_ZIP_FileCreate = 0;

// Creates ZIP storage
ZIPFile* ZIP_FileCreate(const char *path)
{
	return g_memoryCall.Function<ZIPFile*>(Address_ZIP_FileCreate, path);
}

static uintptr_t Address_ZIP_AddStorage = 0;

// Adds ZIP storage
bool ZIP_AddStorage(ZIPFile* toAdd)
{
	return g_memoryCall.Function<bool>(Address_ZIP_AddStorage, toAdd);
}

// Initialize
void ZIP_VarInitialisation::Initialise()
{
	MAKE_VAR_GAME_VERSION();

	MAKE_DEAD_IF();
#ifdef IS_PLATFORM_ANDROID
	Address_ZIP_FileCreate = (uintptr_t)Library::GetSymbolAddress(&g_LimitAdjuster.hModule_of_game, "_Z14ZIP_FileCreatePKc");
	Address_ZIP_AddStorage = (uintptr_t)Library::GetSymbolAddress(&g_LimitAdjuster.hModule_of_game, "_Z14ZIP_AddStorageP7ZIPFile");
#endif
}