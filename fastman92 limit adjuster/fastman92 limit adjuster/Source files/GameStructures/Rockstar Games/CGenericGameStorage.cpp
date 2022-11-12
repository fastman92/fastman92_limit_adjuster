#include "CGenericGameStorage.h"
#include "../../Core/LimitAdjuster.h"

using namespace Game;

CGenericGameStorage_VarInitialisation g_CGenericGameStorage_VarInitialisation;

static void* ptrCGenericGameStorage__SaveDataToWorkBuffer = 0;

char** CGenericGameStorage::ms_WorkBuffer = 0;
unsigned int* CGenericGameStorage::ms_FilePos = 0;
unsigned int* CGenericGameStorage::ms_WorkBufferSize = 0;
unsigned int* CGenericGameStorage::ms_WorkBufferPos = 0;

// Checksum
uint32_t* CGenericGameStorage::ms_CheckSum = 0;

// Writes to save file
int CGenericGameStorage::SaveDataToWorkBuffer(const void *pSource, int Size)
{
	return ((int(*) (const void *pSource, int Size))ptrCGenericGameStorage__SaveDataToWorkBuffer)(pSource, Size);
}

static void* ptrCGenericGameStorage__LoadDataFromWorkBuffer = 0;

// Reads to save file
bool CGenericGameStorage::LoadDataFromWorkBuffer(void *ptr, unsigned int numOfBytes)
{
	return ((bool(*)(void *ptr, unsigned int numOfBytes))ptrCGenericGameStorage__LoadDataFromWorkBuffer)(ptr, numOfBytes);
}

// Initialize
void CGenericGameStorage_VarInitialisation::Initialise()
{
	MAKE_VAR_GAME_VERSION();

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86
		|| gameVersion == GAME_VERSION_GTA_SA_1_0_US_COMPACT_WIN_X86)
	{
		ptrCGenericGameStorage__SaveDataToWorkBuffer = (void*)g_mCalc.GetCurrentVAbyPreferedVA(0x5D1270);
		ptrCGenericGameStorage__LoadDataFromWorkBuffer = (void*)g_mCalc.GetCurrentVAbyPreferedVA(0x5D1300);
		CGenericGameStorage::ms_WorkBuffer = (char**)g_mCalc.GetCurrentVAbyPreferedVA(0xC16EE8);
		CGenericGameStorage::ms_FilePos = (unsigned int*)g_mCalc.GetCurrentVAbyPreferedVA(0xC16EF4);
		CGenericGameStorage::ms_WorkBufferSize = (unsigned int*)g_mCalc.GetCurrentVAbyPreferedVA(0x8D2BE0);
		CGenericGameStorage::ms_WorkBufferPos = (unsigned int*)g_mCalc.GetCurrentVAbyPreferedVA(0xC16EEC);
		CGenericGameStorage::ms_CheckSum = (uint32_t*)g_mCalc.GetCurrentVAbyPreferedVA(0xC16134);
	}
	#elif defined(IS_PLATFORM_ANDROID_ARM32)
	ptrCGenericGameStorage__SaveDataToWorkBuffer = (void*)Library::GetSymbolAddress(
		&g_LimitAdjuster.hModule_of_game,
		"_ZN19CGenericGameStorage21_SaveDataToWorkBufferEPvi"
	);
	ptrCGenericGameStorage__LoadDataFromWorkBuffer = (void*)Library::GetSymbolAddress(
		&g_LimitAdjuster.hModule_of_game,
		"_ZN19CGenericGameStorage23_LoadDataFromWorkBufferEPvi"
	);

	CGenericGameStorage::ms_WorkBuffer = (char**)Library::GetSymbolAddress(
		&g_LimitAdjuster.hModule_of_game,
		"_ZN19CGenericGameStorage13ms_WorkBufferE"
	);

	CGenericGameStorage::ms_FilePos = (unsigned int*) Library::GetSymbolAddress(
		&g_LimitAdjuster.hModule_of_game,
		"_ZN19CGenericGameStorage10ms_FilePosE"
	);

	CGenericGameStorage::ms_WorkBufferSize = (unsigned int*)Library::GetSymbolAddress(
		&g_LimitAdjuster.hModule_of_game,
		"_ZN19CGenericGameStorage17ms_WorkBufferSizeE"
	);

	CGenericGameStorage::ms_WorkBufferPos = (unsigned int*)Library::GetSymbolAddress(
		&g_LimitAdjuster.hModule_of_game,
		"_ZN19CGenericGameStorage16ms_WorkBufferPosE"
	);

	CGenericGameStorage::ms_CheckSum = (uint32_t*)Library::GetSymbolAddress(
		&g_LimitAdjuster.hModule_of_game,
		"_ZN19CGenericGameStorage11ms_CheckSumE"
	);
	#endif
}