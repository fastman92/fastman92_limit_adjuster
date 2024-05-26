#include "OSMutex.h"

#include "../../Core/LimitAdjuster.h"

OSMutex_VarInitialisation g_OSMutex_VarInitialisation;

static uintptr_t Address_OS_MutexObtain = 0;

void OS_MutexObtain(OSMutex onMutex)
{
	return g_memoryCall.Function<void>(Address_OS_MutexObtain, onMutex);
}

static uintptr_t Address_OS_MutexRelease = 0;

void OS_MutexRelease(OSMutex onMutex)
{
	return g_memoryCall.Function<void>(Address_OS_MutexRelease, onMutex);
}

// Initialize
void OSMutex_VarInitialisation::Initialise()
{
	MAKE_VAR_GAME_VERSION();

	MAKE_DEAD_IF();
#ifdef IS_PLATFORM_ANDROID
	Address_OS_MutexObtain = (uintptr_t)Library::GetSymbolAddress(&g_LimitAdjuster.hModule_of_game, "_Z14OS_MutexObtainPv");
	Address_OS_MutexRelease = (uintptr_t)Library::GetSymbolAddress(&g_LimitAdjuster.hModule_of_game, "_Z15OS_MutexReleasePv");	
#endif
}