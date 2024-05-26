/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include <Assertions.h>
#include "../Core/CPatch.h"
#include "../Core/CCodeMover.h"
#include "../Core/CLimitAdjusterModule.h"
#include "../Core/FormattedOutput.h"

#include "../GameStructures/Rockstar Games/CCollisionFile.h"
#include "../GameStructures/Rockstar Games/CIplFile.h"
#include "../GameStructures/Rockstar Games/CModelInfo.h"
#include "../GameStructures/Rockstar Games/CPool.h"
#include "../GameStructures/Rockstar Games/CStreamingInfo.h"
#include "../GameStructures/Rockstar Games/CUnlimitedStore.h"
#include "../GameStructures/Rockstar Games/CVehicleRecordingFileInfo.h"
#include "../GameStructures/Rockstar Games/TxdDef.h"

#include "../ForOtherProjects/Common/CdDirectory.h"

#include <Android\preferedUnorderedMap.h>
#include <enumMemberNamePair.h>
#include <EnumOperators.h>
#include <Exception/exception.h>

/*
	GTA SA 1.0 WIN_X86

	CModelInfo::SetModelInfo - 0x4C5530
	CModelInfo::GetModelInfo - 0x403DA0

*/

typedef int32_t tFileTypeBaseID;
typedef int32_t tFileTypeLimit;

enum eFileTypeGeneral
{
	GENERAL_FILE_TYPE_UNDEFINED,

	GENERAL_FILE_TYPE_MODEL_ARCHIVE,
	GENERAL_FILE_TYPE_TEXTURE_ARCHIVE,
	GENERAL_FILE_TYPE_COLLISION_ARCHIVE,
	GENERAL_FILE_TYPE_ANIMATION_ARCHIVE,
	GENERAL_FILE_TYPE_ITEM_DEFINITION,
	GENERAL_FILE_TYPE_ITEM_PLACEMENT,
	GENERAL_FILE_TYPE_PATH_NODES,
	GENERAL_FILE_TYPE_CAR_RECORDING,
	GENERAL_FILE_TYPE_SCM,
	GENERAL_FILE_TYPE_LUA
};

#define MAKE_FILE_TYPE_LIST(formatMacro) \
	formatMacro(FILE_TYPE_MODEL, GENERAL_FILE_TYPE_MODEL_ARCHIVE) \
	formatMacro(FILE_TYPE_DFF, GENERAL_FILE_TYPE_MODEL_ARCHIVE) \
	formatMacro(FILE_TYPE_NIF, GENERAL_FILE_TYPE_MODEL_ARCHIVE) \
	formatMacro(FILE_TYPE_TXD, GENERAL_FILE_TYPE_TEXTURE_ARCHIVE) \
	formatMacro(FILE_TYPE_NFT, GENERAL_FILE_TYPE_TEXTURE_ARCHIVE) \
	formatMacro(FILE_TYPE_WTD, GENERAL_FILE_TYPE_TEXTURE_ARCHIVE) \
	formatMacro(FILE_TYPE_COL, GENERAL_FILE_TYPE_COLLISION_ARCHIVE) \
	formatMacro(FILE_TYPE_AGR, GENERAL_FILE_TYPE_UNDEFINED) \
	formatMacro(FILE_TYPE_IPB, GENERAL_FILE_TYPE_ITEM_PLACEMENT) \
	formatMacro(FILE_TYPE_IPL, GENERAL_FILE_TYPE_ITEM_PLACEMENT) \
	formatMacro(FILE_TYPE_MAP_PLACEMENT, GENERAL_FILE_TYPE_ITEM_PLACEMENT) \
	formatMacro(FILE_TYPE_DAT, GENERAL_FILE_TYPE_PATH_NODES) \
	formatMacro(FILE_TYPE_IFP, GENERAL_FILE_TYPE_ANIMATION_ARCHIVE) \
	formatMacro(FILE_TYPE_WAD, GENERAL_FILE_TYPE_ANIMATION_ARCHIVE) \
	formatMacro(FILE_TYPE_RRR, GENERAL_FILE_TYPE_CAR_RECORDING) \
	formatMacro(FILE_TYPE_LIP, GENERAL_FILE_TYPE_UNDEFINED) \
	formatMacro(FILE_TYPE_CAT, GENERAL_FILE_TYPE_UNDEFINED) \
	formatMacro(FILE_TYPE_SCM, GENERAL_FILE_TYPE_SCM) \
	formatMacro(FILE_TYPE_LUR, GENERAL_FILE_TYPE_UNDEFINED) \
	formatMacro(FILE_TYPE_LOADED_START, GENERAL_FILE_TYPE_UNDEFINED) \
	formatMacro(FILE_TYPE_REQUESTED_START, GENERAL_FILE_TYPE_UNDEFINED) \

// #define PUT_ENUM_MEMBER_FROM_LIST(member, generalFileType) member,

enum eFileType
{
	MAKE_FILE_TYPE_LIST(PUT_ENUM_MEMBER_FROM_LIST)

	FILE_TYPE_UNDEFINED,

	FILE_TYPE_ENUM_MAX = FILE_TYPE_UNDEFINED,
	FILE_TYPE_FIRST = FILE_TYPE_MODEL
};

// DEFINE_ENUM_OPERATORS(eFileType);

struct tFileTypeDescriptor
{
	eFileType fileType;
	const char* fileTypeName;
	eFileTypeGeneral generalFileType;
};

class CFileTypeInfo
{
public:
	static const tFileTypeDescriptor fileDescriptorArray[];

	/* Finds enum member by name */
	static eFileType GetEnumMemberByName(const char* name);

	/* Finds name by enum member */
	static const char* GetEnumNameByMember(eFileType member);

	/* Finds general file type descriptor by enum member */
	static const tFileTypeDescriptor* GetFileInfoDescriptorByMember(eFileType member);
};

// GTA Vice City
namespace Game_GTAVC
{
	struct CAnimBlock
	{
	  char animName[20];
	  char loaded;
	  int16_t usageCount;
	  int field_18;
	  int field_1C;
	};

	VALIDATE_SIZE(CAnimBlock, 0x20);
};

// GTA San Andreas
namespace Game_GTASA
{
	struct CAnimBlock
	{
		char name[16];
		char loaded;
		char field_11;
		int16_t usageCount;
		int startAnimation;
		int animationCount;
		int animationStyle;
	};

	VALIDATE_SIZE(CAnimBlock, 0x20);
	
	struct CStreamedScriptInfo
	{
		void *data;
		char status;
		char field_5;
		int16_t wScmIndex;
		char name[20];
		int size;
	};

	VALIDATE_SIZE_ONLY_ON_32_BIT_ARCHITECTURE(CStreamedScriptInfo, 0x20);
	VALIDATE_SIZE_ONLY_ON_64_BIT_ARCHITECTURE(CStreamedScriptInfo, 0x28);

	struct CStreamedScripts_Footer
	{
		int largestExternalSize;
		int16_t countOfScripts;
		int16_t field_A46;
	};

	// CDarkel
	class CDarkel
	{
	public:
		// Finds total number of peds killed by player.
		static int __cdecl FindTotalPedsKilledByPlayer(int playerID);
	};

	struct ListItem_c
	{
		int pPrev;
		int pNext;
	};
	
	struct Furniture_c : ListItem_c
	{
		uint16_t m_wModelIndex;
		int16_t field_A;
		char field_C;
		char field_D;
		char field_E;
		char field_F;
		char field_10;
		char field_11;
		char field_12;
		char field_13;
	};

#ifdef IS_ARCHITECTURE_32_BIT
	VALIDATE_SIZE(Furniture_c, 0x14);
#endif
}

class CStreamingInfoExtension
{
public:
	uint32_t dwSize;
	int32_t exUsNext;
	int32_t exUsPrev;
	int32_t exNextOnCd;

	uint32_t m_NumberOfPaddedBytesInAlignedOriginalSize;

	uint32_t m_PackedSizeInSectors;

	uint32_t m_NumberOfPaddedBytesInAlignedPackedSize;

	uint32_t m_exFlags;

#ifdef STORE_FILE_NAME_FIELD_IN_CSTREAMINGINFO_EXTENSION
	char m_Filename[IMG_FASTMAN92_GTASA_MAX_FILENAME_LENGTH];
#endif

	// Initialize
	void Init();
};

struct tFileTypeInfo
{
	tFileTypeLimit maxLimitValue;	// 0 - cannot be changed

	eFileType fileType;
	const tFileTypeDescriptor* pFileTypeDescriptor;	// can be NULL
	
	tFileTypeBaseID currentBaseID;
	tFileTypeLimit currentLimitValue;
	tFileTypeBaseID defaultBaseID;
	tFileTypeLimit defaultLimitValue;
};

namespace details
{
	// ID limit hacks
	class FileIDlimit_base1 :
		public CLimitAdjusterModule
	{
	protected:
		tFileTypeInfo fileTypeArray[32];
		int countOfTypes;		

	public:
		/////////// eFileType        ///////////
		// Returns pointer to file type info
		const tFileTypeInfo* GetFileTypeInfo(eFileType type) const;

		// Returns pointer to file type info
		tFileTypeInfo* GetFileTypeInfo(eFileType type)
		{
			return const_cast<tFileTypeInfo*>(static_cast<const FileIDlimit_base1*>(this)->GetFileTypeInfo(type));
		}

		/////////// eFileTypeGeneral ///////////

		// Returns pointer to file type info
		const tFileTypeInfo* GetFileTypeInfo(eFileTypeGeneral type) const;

		// Returns pointer to file type info
		tFileTypeInfo* GetFileTypeInfo(eFileTypeGeneral type)
		{
			return const_cast<tFileTypeInfo*>(static_cast<const FileIDlimit_base1*>(this)->GetFileTypeInfo(type));
		}
	};
}

template <typename enumType, class existingClass> class FileIDlimit_commonStuff : public existingClass
{
public:
	// Can limit be changed?
	bool CanLimitBeChanged(enumType type) const
	{
		const tFileTypeInfo* pFileInfo = this->GetFileTypeInfo(type);

		return pFileInfo ? pFileInfo->maxLimitValue != 0 : 0;
	}

	// Returns base ID
	tFileTypeBaseID GetBaseID(enumType type) const
	{
		const tFileTypeInfo* pFileInfo = this->GetFileTypeInfo(type);

		return pFileInfo ? pFileInfo->currentBaseID : 0;
	}

	// Returns default base ID
	tFileTypeBaseID GetDefaultBaseID(enumType type) const
	{
		const tFileTypeInfo* pFileInfo = this->GetFileTypeInfo(type);

		return pFileInfo ? pFileInfo->defaultBaseID : 0;
	}

	// Returns last available ID for type
	tFileTypeBaseID GetLastIDforType(enumType type) const
	{
		return GetBaseID(type) + GetFileIDcurrentLimit(type) - 1;
	}

	// Returns ID limit default value
	tFileTypeLimit GetFileIDdefaultLimit(enumType type) const
	{
		const tFileTypeInfo* pFileInfo = this->GetFileTypeInfo(type);

		return pFileInfo ? pFileInfo->defaultLimitValue : 0;
	}

	// Returns ID limit current value
	tFileTypeLimit GetFileIDcurrentLimit(enumType type) const
	{
		const tFileTypeInfo* pFileInfo = this->GetFileTypeInfo(type);

		return pFileInfo ? pFileInfo->currentLimitValue : 0;
	}

	// Sets ID limit
	void SetFileIDlimit(enumType type, tFileTypeLimit limit, bool bRequireIDlimitToBeChanged = true)
	{
		tFileTypeInfo* pFileInfo = this->GetFileTypeInfo(type);

		if (!pFileInfo)
		{
			if (bRequireIDlimitToBeChanged)
				throw f92_runtime_error("Value of certain ID limit cannot be changed. Editing this limit currently unsupported. Current value: %d",				
					limit
				);
		}
		else if(pFileInfo->maxLimitValue == 0)
		{
			if (bRequireIDlimitToBeChanged)
				throw f92_runtime_error("Value of %s cannot be changed. Editing this limit currently unsupported. Current value: %d",
					CFileTypeInfo::GetEnumNameByMember(type),
					limit
				);
		}
		else if (limit > pFileInfo->maxLimitValue)
		{
			if (bRequireIDlimitToBeChanged)
				throw f92_runtime_error("Value of %s cannot be so high. Max possible value is %d. Current value: %d",
					CFileTypeInfo::GetEnumNameByMember(type),
					pFileInfo->maxLimitValue,
					limit
				);
		}
		else
			pFileInfo->currentLimitValue = limit;
	}
};
///////////////////////////////////////////////////////////

namespace details
{
	typedef FileIDlimit_commonStuff<eFileType, FileIDlimit_base1> FileIDlimit_base_withFileType;
	typedef FileIDlimit_commonStuff<eFileTypeGeneral, FileIDlimit_base_withFileType> FileIDlimit_base_withFileTypeGeneral;
}

 struct tIDhashPair
 {
	 int32_t ID;
	 uint32_t hash;
 };

 class CIDHashContainerBase
 {
 public:

 #ifdef __clang__
 #pragma clang diagnostic push
 #pragma clang diagnostic ignored "-Winfinite-recursion"
 #endif

	 // Allocate element
	 virtual void AllocateElement(int32_t ID, uint32_t hash) { this->AllocateElement(ID, hash); }

	 // Updates element
	 virtual void UpdateElement(int32_t ID, uint32_t oldHash, uint32_t newHash)
	 {
		 this->UpdateElement(ID, oldHash, newHash);
	 }

 #ifdef __clang__
 #pragma clang diagnostic pop
 #endif

	 // Returns ID by hash
	 virtual int32_t GetIDbyHashBinarySearch(uint32_t hash) = 0;

	 // Clears the array
	 virtual void Clear() = 0;
 };

class CIDHashContainerDelayedSorting : public CIDHashContainerBase
 {
 public:
	 typedef std::vector<tIDhashPair> tEntryContainer;
	 tEntryContainer array;
	 bool bIsArraySorted;
 public:

	 // Constructor
	 CIDHashContainerDelayedSorting();

	 // Allocate element
	 void AllocateElement(int32_t ID, uint32_t hash);

	 // Updates element
	 void UpdateElement(int32_t ID, uint32_t oldHash, uint32_t newHash);

	 // Returns ID by hash
	 int32_t GetIDbyHashBinarySearch(uint32_t hash);

	 // Returns ID by hash
	 int32_t GetIDbyHashLinearSearch(uint32_t hash);

	 // Returns element iterator by ID
	 tEntryContainer::iterator GetElementItByID(int32_t ID);
	 
	 // Sorts the array
	 void SortTheArray();

	 // Clears the array
	 void Clear();
};

class CIDHashContainerAlwaysSorted : public CIDHashContainerBase
{
	// <hash, ID>

	typedef prefered_unordered_map<uint32_t, int32_t> tEntryContainer;
	tEntryContainer array;


public:
	// Allocate element
	void AllocateElement(int32_t ID, uint32_t hash);

	// Updates element
	void UpdateElement(int32_t ID, uint32_t oldHash, uint32_t newHash);

	// Updates element
	void RemoveElement(int32_t ID, uint32_t oldHash);

	// Returns ID by hash
	int32_t GetIDbyHashBinarySearch(uint32_t hash);

	// Clears the array
	void Clear();
};

class FileIDlimit : public details::FileIDlimit_base_withFileTypeGeneral
{
public:
	// Make functions visible
	using details::FileIDlimit_base_withFileType::CanLimitBeChanged;
	using details::FileIDlimit_base_withFileTypeGeneral::CanLimitBeChanged;
	using details::FileIDlimit_base_withFileType::GetBaseID;
	using details::FileIDlimit_base_withFileTypeGeneral::GetBaseID;
	using details::FileIDlimit_base_withFileType::GetDefaultBaseID;
	using details::FileIDlimit_base_withFileTypeGeneral::GetDefaultBaseID;
	using details::FileIDlimit_base_withFileType::GetFileIDcurrentLimit;
	using details::FileIDlimit_base_withFileTypeGeneral::GetFileIDcurrentLimit;
	using details::FileIDlimit_base_withFileType::GetFileIDdefaultLimit;
	using details::FileIDlimit_base_withFileTypeGeneral::GetFileIDdefaultLimit;
	using details::FileIDlimit_base_withFileType::GetLastIDforType;
	using details::FileIDlimit_base_withFileTypeGeneral::GetLastIDforType;
	using details::FileIDlimit_base_withFileType::SetFileIDlimit;
	using details::FileIDlimit_base_withFileTypeGeneral::SetFileIDlimit;

private:
	uint32_t maxCountOfIDs;

	bool bIDlimitsKnown;
	bool bIDlimitsPatchEnabled;

	// Returns array index
	int GetFileTypeArrayIndex(eFileType type);

public:
	// Registers file type
	void RegisterFileType(eFileType fileType, int defaultCount, tFileTypeLimit maxLimitValue);

	// Returns maximum number of file IDs
	uint32_t GetMaxNumberOfFileIDs() const;

	// Returns true, if there is any ID limit that can be modified
	bool IsThereAnyIDlimitThatCanBeModified() const;

	// Writes to log if limits are changed
	bool WriteToLogIfLimitsAreChanged(bool bModelSpecialFeaturesImplemented = false);

	// Updates base IDs, needs to be executed 
	void UpdateBaseIDs();

	// Enables/disables ID limits patch.
	void EnableIDlimitsPatch(bool bEnabled);

	// Returns true if ID limits are known
	bool AreIDlimitsKnown() const;

	// Returns true if ID limits patch is enabled
	bool IsIDlimitsPatchEnabled() const;

	// Returns true if any ID limit is increased.
	bool IsAnyIDlimitIncreased() const;

	// Returns true if any ID limit is changed.
	bool IsAnyIDlimitChanged() const;

	// Sets ID limits to default values.
	void SetIDlimitsToDefaultValues();

	// Returns count of all file IDs
	tFileTypeBaseID GetCountOfAllFileIDs() const { return fileTypeArray[countOfTypes].currentBaseID; }

	// Returns count of all file IDs
	tFileTypeBaseID GetDefaultCountOfAllFileIDs() const { return fileTypeArray[countOfTypes].defaultBaseID; }	

	// Returns count of types
	int GetCountOfTypes() const { return countOfTypes; }

	// Returns file type info by index
	tFileTypeInfo* GetFileTypeInfoByIndex(int index);

	// Returns type of file ID
	eFileType GetFileIDtype(tFileTypeBaseID fileID) const
	{
		for (int i = 0; i < countOfTypes; ++i)
		{
			if (fileID < this->fileTypeArray[i + 1].currentBaseID)
				return this->fileTypeArray[i].fileType;
		}

		return FILE_TYPE_UNDEFINED;
	}

public:

	// models
	struct {
		union {
			CBaseModelInfo_generic** generic;
			Game_GTAIII::CBaseModelInfo** gta_iii;
			Game_GTAVC::CBaseModelInfo** gta_vc;
			Game_GTASA::CBaseModelInfo** gta_sa;
			Game_GTAIV::CBaseModelInfo** gta_iv;
			Game_BullyScholarschipEdition::CBaseModelInfo** bully_se;
		};

		DEFINE_IS_ALLOCATED();
	} CModelInfo__ms_modelInfoPtrs;

	CUnlimitedStore<CBaseModelInfo_extension> CModelInfo__ms_modelInfoExtensionStore;
	CBaseModelInfo_extension** CModelInfo__ms_modelInfoExtensionPtrs;

	CIDHashContainerDelayedSorting CModelInfo__ms_modelInfoIDhashStore;

	struct {
		uint32_t *  ptr;
		DEFINE_IS_ALLOCATED();
	} CSimpleModelInfo__m_UpdatedUVATable;

	// TXD archives
	union {
		CPool_GTASA<Game_GTASA::TxdDef>** gta_sa;
		CPool_GTASA<Game_GTASA::TxdDef_Android>** gta_sa_android;
		CPool_GTAIV<Game_GTAIV::TxdDef>** gta_iv;
	} CTxdStore__pTxdPool;

	CIDHashContainerAlwaysSorted CTxdStore__pTxdHashStore;

	// files
	struct {
		union {
			void* generic;
			Game_GTAIII::CStreamingInfo* gta_iii;
			Game_GTAVC::CStreamingInfo* gta_vc;
			Game_GTASA::CStreamingInfo* gta_sa;
			Game_BullyScholarschipEdition::CStreamingInfo* bully_se;
		};
		DEFINE_IS_ALLOCATED();
	} CStreaming__ms_aInfoForModel;

	unsigned int NumberOfStreamingInfos;

	CStreamingInfoExtension* CStreaming__ms_aInfoForModelExtension;

	// IPL files
	union {
		CPool_GTASA<Game_GTASA::CIplFile>** gta_sa;
	} CIplStore__ms_pPool;

	// anims
	struct {
		union {
			void* generic;
			Game_GTAVC::CAnimBlock* gta_vc;
			Game_GTASA::CAnimBlock* gta_sa;
		};
		DEFINE_IS_ALLOCATED();
	} CAnimManager__ms_aAnimBlocks;

	// recordings
	struct {
		union {
			void* generic;
			Game_GTASA::CVehicleRecordingFileInfo* gta_sa;
			Game_GTAIV::CVehicleRecordingFileInfo* gta_iv;
		};
		DEFINE_IS_ALLOCATED();
	} CVehicleRecording__StreamingArray;

	// collision archives
	union {
		CPool_GTASA<Game_GTASA::CCollisionFile>** gta_sa;
	} CColStore__ms_pColPool;

	CCollisionFile_extension* CColStore__ms_aColPoolExtension;

	// AGR files
	struct {
		union {
			void* generic;
			void** bully_se;
		};
		DEFINE_IS_ALLOCATED();
	} CStreaming__ms_apAGRBuffers;

	// streamed scripts
	struct {
		char* ptr;
		DEFINE_IS_ALLOCATED();
	} CTheScripts__StreamedScripts;

	// lists
	void** CStreaming__ms_pStartRequestedList;
	void** CStreaming__ms_pEndRequestedList;
	void** CStreaming__ms_pStartLoadedList;
	void** CStreaming__ms_pEndLoadedList;

	/////
	bool bIsModelInfoExtensionArrayEnabled;
	bool bIsFileInfoExtensionArrayEnabled;
	bool bIsCollisionFileExtensionArrayEnabled;

	/////////////////// evolution booleans
	bool bIsIDunsigned;
	bool bIsIDbaseInt32;
	bool bAreDifficultFileTypesInt32;	

	bool bIsCOLIDsizeIncreased;
	bool bIsIPLIDsizeIncreased;
	//////////////////

	bool bIsPatchForLoadingSaveBlocksApplied;

	// Count of killable model IDs
	unsigned int CDarkel__CountOfKillableModelIDs;

	// Registered kills
	struct {
		int16_t* ptr;
		DEFINE_IS_ALLOCATED();
	} CDarkel__RegisteredKills;
	
	// Initialize must be called before any other function
	virtual void Initialise();

	// Shutdown
	virtual void Shutdown();

	// Patches save loading functions.
	void PatchSaveBlockLoadingFunctions();

	// Patches ID limit if neccessary.
	void PatchFileIDlimits();

	// Patches count of killable model IDs
	void PatchCountOfKillableModelIDs(int iCountOfKillableModelIDs);

	// Patch: file binary search by name
	void PatchUseFileBinarySearchByName();

	// Allocates model info extension item
	CBaseModelInfo_extension* AllocateModelInfoExtensionItemIfNeccessary(int modelID);

private:
	// Allocates model extension if enabled
	void AllocateModelInfoExtensionArrayIfEnabled();

	// Allocates file extension if enabled
	void AllocateFileInfoExtensionArrayIfEnabled();

	// Allocates collision file extension if enabled
	void AllocateCollisionFileExtensionArrayIfEnabled();

	// Sets variables
	void SetVariables();

	#ifdef IS_PLATFORM_WIN_X86
	// Patches ID limits if neccessary.
	void PatchFileIDlimits_GTA_III_1_0();

	// Patches ID limits if neccessary.
	void PatchFileIDlimits_GTA_VC_1_0();

	// Patches ID limit if neccessary.
	void PatchFileIDlimits_GTA_SA_PC_1_0_HOODLUM();

	// Patches ID limits if neccessary.
	void PatchFileIDlimits_GTA_IV_1_0_7_0();

	// Patches ID limits if neccessary.
	void PatchFileIDlimits_GTA_IV_1_0_8_0();

	// Patches ID limits if neccessary.
	void PatchFileIDlimits_GTA_EFLC_1_1_2_0();

	// Patches ID limits if neccessary.
	void PatchFileIDlimits_Bully_SE_1_20();
	#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
	// Patches ID limits if neccessary.
	void PatchFileIDlimits_GTA_SA_2_0_ARMEABI_V7A();
	#elif defined(IS_PLATFORM_ANDROID_ARM64_V8A)
	// Patches ID limits if neccessary.
	void PatchFileIDlimits_GTA_SA_2_11_32_ANDROID_ARM64_V8A();
	#endif

	// Patches ID limits if neccessary.
	void PatchFileIDlimits_GTA_SA();

	#if IS_ARCHITECTURE_32_BIT
	// Patches ID limits if neccessary.
	void PatchFileIDlimits_GTA_IV_or_EFLC();
	#endif

public:

	// Enables model info model extension array
	void EnableModelInfoExtensionArray();

	// Enables file info model extension array
	void EnableFileInfoExtensionArray();

	// Enables collision file extension array
	void EnableCollisionFileExtensionArray();

	// Allocates neccessary arrays
	void AllocateNeccessaryArrays();

	// Is special model ID?
	bool IsSpecialModelID(int32_t ID);

	// Returns number of file IDs
	virtual int32_t GetNumberOfFileIDs() {
		return this->GetCountOfAllFileIDs();
	};

	// Returns Prev value 
	virtual int32_t GetFileInfoPrev(int32_t fileID);

	// Returns Next value
	virtual int32_t GetFileInfoNext(int32_t fileID);

	// Returns NextOnCD value
	virtual int32_t GetFileInfoNextOnCD(int32_t fileID);

	// Sets Prev value 
	virtual void SetFileInfoPrev(int32_t fileID, int32_t newValue);

	// Sets Next value
	virtual void SetFileInfoNext(int32_t fileID, int32_t newValue);

	// Sets NextOnCD value
	virtual void SetFileInfoNextOnCD(int32_t fileID, int32_t newValue);

	////////////////
	// Finds model ID by model info
	int32_t FindModelIDbyModelInfo(CBaseModelInfo_generic* pModelInfo);
};

extern FileIDlimit g_fileIDlimits;