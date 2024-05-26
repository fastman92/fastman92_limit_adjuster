#include "OSFile.h"

#define __STDC_LIMIT_MACROS
#include <stdint.h>
#include <string.h>
#include <string>

#include <sys/stat.h>

#include "../../GameStructures/CMemoryAllocationByApp.h"
#include "../../Core/LimitAdjuster.h"
#include "../../Core/FormattedOutput.h"

#include "OSMutex.h"
#include "ZIPFile.h"

OSFile_VarInitialisation g_OSFile_VarInitialisation;

#if IS_PLATFORM_ANDROID
static OSMutex* fileMutex;

uintptr_t Address_NvFOpen = 0;

// directoryPath can be NULL
NvFileHandle* NvFOpen(const char* directoryPath, const char* filename, bool userOnly, bool checkAPK)
{
	return g_memoryCall.Function<NvFileHandle*>(Address_NvFOpen, directoryPath, filename, userOnly, checkAPK);
}

static uintptr_t Address_NvFIsApkFile = 0;

bool NvFIsApkFile(NvFile *file)
{
	return g_memoryCall.Function<bool>(Address_NvFIsApkFile, file);
}

// Constructor
AndroidFile::AndroidFile()
{
	this->readBuffer = 0;
	this->fileAsync = 0;
	this->justCreated = false;
	this->readFileHandle = 0;
	this->writeFileHandle = 0;
	this->nextAsyncFile = 0LL;
	this->subLength = UINT32_MAX;
	this->subOffset = UINT32_MAX;
}

AndroidFile** AndroidFile::firstAsyncFile;

OSFileError OS_FileOpen_replacement(
	OSFileDataArea area,
	OSFile *intoFile,
	const char *filename,
	OSFileAccessType access)
{

	// file can only be written in user area
	bool userOnly = area == OSFDA_User_0 || access == OSFAT_Write_0 || access == OSFAT_ReadWrite_0;

	AndroidFile* ResultFile = new_by_app AndroidFile;
	
	if (!strncmp(filename, ".\\", 2u) || !strncmp(filename, "./", 2u))
		filename += 2;

	std::string filepath;

	std::string filenameLowerCase = filename;

	if (*filename != '/')
	{
		std::transform(filenameLowerCase.begin(), filenameLowerCase.end(), filenameLowerCase.begin(),
			[](unsigned char c) { return std::tolower(c); });
	}
	
	////
	const char* BasePath = "";
	const char* StorageRootBuffer = g_LimitAdjuster.StorageRootDirectory;	
	////
	

	if (userOnly)
	{
		filepath = StorageRootBuffer;
		filepath += BasePath;

		mkdir(filepath.c_str(), 0771);
	}
	else
		filepath = BasePath;

	size_t basicLen = filepath.length();

	filepath += filenameLowerCase;

	std::transform(filepath.begin(), filepath.end(), filepath.begin(),
		[](unsigned char c) { return c == '\\' ? '/' : c; });

	// Trim path from the right side
	if (filepath.length() > 0)
	{
		auto lastGood = filepath.end() - 1;

		while (true)
		{
			char c = *lastGood;

			if (c != ' ' && (unsigned int)(c - 9) > 4)
				break;

			lastGood--;
		}

		filepath.erase(lastGood + 1, filepath.end());
	}

	////
	// Now there is filepath to open
	switch (access)
	{
		case OSFAT_Read_0:
		case OSFAT_ReadAsync_0:
			if (*filename != '/' && !userOnly)
				ResultFile->readFileHandle = NvFOpen(BasePath, filepath.c_str() + basicLen, false, 1);
			else
				ResultFile->readFileHandle = NvFOpen(0, filepath.c_str() + basicLen, userOnly, 1);

			// ZIP Storage functionality
		TryZIPStorage:
			// WarDrums has made a memory leak by returning the handle from ZIPFile::OpenFromStorage and forgetting about ResultFile that was allocated before.

			if (!ResultFile->readFileHandle && !userOnly)
			{
				AndroidFile* resultFromZIPstorage = (AndroidFile*)ZIPFile::OpenFromStorage(filepath.c_str() + basicLen, access);

				if(resultFromZIPstorage)
					*ResultFile = *resultFromZIPstorage;
			}

			////

			if (access == OSFAT_ReadAsync_0 && NvFIsApkFile(ResultFile->readFileHandle))
			{
				OS_MutexObtain(*fileMutex);
				ResultFile->fileAsync = true;
				AndroidFile* firstAsyncFile = *AndroidFile::firstAsyncFile;
				*AndroidFile::firstAsyncFile = ResultFile;
				ResultFile->nextAsyncFile = firstAsyncFile;
				OS_MutexRelease(*fileMutex);
			}
			break;
		case OSFAT_Write_0:
			ResultFile->writeFileHandle = fopen(filepath.c_str(), "wb");
			break;

		case OSFAT_ReadWrite_0:
			ResultFile->writeFileHandle = fopen(filepath.c_str(), "rb+");

			if (ResultFile->writeFileHandle)
			{
				ResultFile->writeFileHandle = fopen(filepath.c_str(), "wb+");
				ResultFile->justCreated = true;
			}
			break;

		default:
			break;
	}

	if (ResultFile->readFileHandle || ResultFile->writeFileHandle)
	{
		*intoFile = ResultFile;

		return OSFE_NoError;
	}
	else
	{
		*intoFile = nullptr;

		delete_by_app_single(ResultFile);

		return OSFE_FileNotFound;
	}
}
#endif

// Initialize
void OSFile_VarInitialisation::Initialise()
{
	MAKE_VAR_GAME_VERSION();

	MAKE_DEAD_IF();
#ifdef IS_PLATFORM_ANDROID
	Address_NvFOpen = (uintptr_t)Library::GetSymbolAddress(&g_LimitAdjuster.hModule_of_game, "_Z7NvFOpenPKcS0_bb");
	Address_NvFIsApkFile = (uintptr_t)Library::GetSymbolAddress(&g_LimitAdjuster.hModule_of_game, "_Z12NvFIsApkFilePv");
	AndroidFile::firstAsyncFile = (AndroidFile**)Library::GetSymbolAddress(&g_LimitAdjuster.hModule_of_game, "_ZN11AndroidFile14firstAsyncFileE");
	fileMutex = (OSMutex*)Library::GetSymbolAddress(&g_LimitAdjuster.hModule_of_game, "fileMutex");
#endif
}