/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "StructureExtension.h"

#include "FileIDlimit.h"
#include "OtherLimits.h"
#include "WeaponLimits.h"

#include "../Core/CGenericLogStorage.h"
#include "../Core/LimitAdjuster.h"
#include "../Core/ProjectConstants.h"

using namespace Game;

StructureExtension g_structureExtension;

#define DEFINE_EXT_FUNCTION_NEW(type) \
static void NewExtended##_##type(type##_generic* pEntity) \
{ \
CGenericLogStorage::SaveFormattedTextLn("New entity, basic: 0x%X ext: 0x%X", pEntity, g_structureExtension.m_##type##Extension.New(pEntity)); \
CGenericLogStorage::SaveWorkBuffer(); \
}

#define DEFINE_EXT_FUNCTION_DEL(type) \
static void DeleteExtended##_##type(type##_generic* pEntity) \
{ \
CGenericLogStorage::SaveFormattedTextLn("Delete entity, basic: 0x%X", pEntity); \
CGenericLogStorage::SaveWorkBuffer(); \
g_structureExtension.m_##type##Extension.Delete(pEntity); \
}

//////////////

#define DEFINE_EXT_FUNCTION(type, func) \
static void func##_##type(const type##_generic* pEntity) \
{ \
g_structureExtension.m_##type##Extension.func(pEntity); \
}

// CGenericLogStorage::SaveFormattedTextLn("%s entity: 0x%X", STRINGIFY(func), pEntity); \
// CGenericLogStorage::SaveWorkBuffer(); \


#define DEFINE_NEW_AND_DELETE_EXT_FUNCTIONS(type) \
	DEFINE_EXT_FUNCTION(type, New) \
	DEFINE_EXT_FUNCTION(type, Delete)

// Creates new ID
int32_t* New_ID_from8bit(const void* pBasicID)
{
	int32_t* pID = g_structureExtension.m_ID_extensionFrom8bit.New(pBasicID);
	*pID = -1;
	return pID;
}

// Removes the ID
void Delete_ID_from8bit(const void* pBasicID)
{
	g_structureExtension.m_ID_extensionFrom8bit.Delete(pBasicID);
}

// Creates new ID
int32_t* New_ID_from16bit(const void* pBasicID)
{
	int32_t* pID = g_structureExtension.m_ID_extensionFrom16bit.New(pBasicID);
	*pID = -1;
	
	// CGenericLogStorage::SaveFormattedTextLn("new_ID for 0x%X", pBasicID);
	// CGenericLogStorage::SaveWorkBuffer();

	return pID;
}

// Removes the ID
void Delete_ID_from16bit(const void* pBasicID)
{
#if 0
	int32_t* ptr = g_structureExtension.m_ID_extensionFrom16bit.GetPointerToExtendedData(pBasicID);
#endif

	g_structureExtension.m_ID_extensionFrom16bit.Delete(pBasicID);
	
#if 0
	if (!ptr)
		CGenericLogStorage::SaveFormattedTextLn("fastman92_problem");
	CGenericLogStorage::SaveFormattedTextLn("delete_ID for 0x%X", pBasicID);

	CGenericLogStorage::SaveWorkBuffer();

	if (!ptr)
		printf_MessageBox("fastman92_problem");
#endif
}

/*
#define DEFINE_NEW_AND_DELETE_EXT_FUNCTIONS(type) \
	DEFINE_EXT_FUNCTION_NEW(type) \
	DEFINE_EXT_FUNCTION_DEL(type)
*/

///////////////////////////////////////////////

MAKE_STRUCT_EXT_LIST(DEFINE_NEW_AND_DELETE_EXT_FUNCTIONS);

///////////////////////////////////////////////
#define DEFINE_GET_EXT_DATA(type) type##_extension* GetExtDataFor##type(const type##_generic* basicPtr) { \
	return g_structureExtension.GET_STRUCT_EXT_MEMBER_NAME(type).GetPointerToExtendedData(basicPtr); }

MAKE_STRUCT_EXT_LIST(DEFINE_GET_EXT_DATA);

#define DEFINE_GET_INTEGER_EXT_DATA(type, name) type* GetExtDataPtrFor##name(const void* basicPtr) { \
	return g_structureExtension.GET_INTEGER_EXTENSION_MEMBER_NAME(name).GetPointerToExtendedData(basicPtr); }

extern "C"
{
	MAKE_INTEGER_EXTENSION_LIST(DEFINE_GET_INTEGER_EXT_DATA);
}

// extended ID
extern "C" {
	// Tells if DFF/TXD 32-bit IDs are enabled.
	bool F92_LA_CONVENTION AreDifficultIDsExtended()
	{
		return g_fileIDlimits.bAreDifficultFileTypesInt32;
	}

	// Returns true if vehicles colour IDs extended.
	F92_LA_API bool F92_LA_CONVENTION AreVehicleColourIDsExtended()
	{
		return g_otherLimits.bIsVehicleColorIDextended;
	}
}

#if PROJECT_USE_DEVELOPMENT_INI
extern "C" {
	// Returns number of extended IDs registered.
	F92_LA_API int32_t F92_LA_CONVENTION GetNumberOfExtendedIDsFrom16bitBefore()
	{
		return g_structureExtension.m_ID_extensionFrom16bit.GetCount();
	}
}
#endif

// 16-bit
static void checkLocation(const void* basicPtr, uintptr_t locationChanged)
{
	/*
	{

		int32_t* ptr = g_structureExtension.m_ID_extensionFrom16bit.GetPointerToExtendedData(basicPtr);

		if (!ptr)
		{
			CGenericLogStorage::SaveFormattedTextLn("get_cant_find");
			CGenericLogStorage::SaveWorkBuffer();
			// printf_MessageBox("get_cant_find");
		}
	}
	*/
}

Game_GTASA::CStreamingInfo* CStreaming__ms_aInfoForModel_start = 0;
Game_GTASA::CStreamingInfo* CStreaming__ms_aInfoForModel_end = 0;

static int32_t* GetPointerToExtendedIDfrom16bit(const void* basicPtr)
{
	// part of CStreaming::ms_aInfoForModel?	
	if (basicPtr >= CStreaming__ms_aInfoForModel_start && basicPtr < CStreaming__ms_aInfoForModel_end)
	{
		const FileIDlimit* pFileIDlimits = &g_fileIDlimits;

		if (pFileIDlimits->bIsIDbaseInt32)	// only supported by GTA SA
		{
			int32_t fileID = (Game_GTASA::CStreamingInfo*)basicPtr - CStreaming__ms_aInfoForModel_start;
			uint32_t memberOffset = (char*)basicPtr - (char*)&CStreaming__ms_aInfoForModel_start[fileID];

			CStreamingInfoExtension* pExtension = &g_fileIDlimits.CStreaming__ms_aInfoForModelExtension[fileID];

			switch (memberOffset)
			{
			case 0:
				return &pExtension->exUsNext;
			case 2:
				return &pExtension->exUsPrev;
			case 4:
				return &pExtension->exNextOnCd;
			default:
				return nullptr;
			}
		}
		else
			return nullptr;
	}

	////////
	// default fallback

	return g_structureExtension.m_ID_extensionFrom16bit.GetPointerToExtendedData(basicPtr);
}

int32_t F92_LA_CONVENTION GetExtendedIDfrom16bitBefore(const void* basicPtr) {
	int32_t* ptr = GetPointerToExtendedIDfrom16bit(basicPtr);

	if (ptr)
		return *ptr;
	else
	{
		uint16_t uID = *(uint16_t*)basicPtr;

		if(uID > MAX_FILE_ID_UINT16)	// is it negative ID?
			return *(int16_t*)basicPtr;
		else
			return uID;
	}
}

int32_t GetExtendedIDfrom16bitBeforeFilter(const void* basicPtr, uintptr_t locationChanged)
{
	checkLocation(basicPtr, locationChanged);

	int32_t ID = GetExtendedIDfrom16bitBefore(basicPtr);
	CGenericLogStorage::SaveFormattedTextLn("get_ID, basic 0x%X, returned 0x%X location 0x%X", basicPtr, ID, locationChanged);
	CGenericLogStorage::SaveWorkBuffer();

	return ID;
}

void F92_LA_CONVENTION SetExtendedIDfrom16bitBefore(void* basicPtr, int32_t ID)
{
	int32_t* ptr = GetPointerToExtendedIDfrom16bit(basicPtr);

	if (ptr)
	{
		*ptr = ID;

		if(!PROJECT_USE_DEVELOPMENT_INI)
			*(uint16_t*)basicPtr = ID;
	}
	else
		*(uint16_t*)basicPtr = ID;
}

void SetExtendedIDfrom16bitBeforeFilter(void* basicPtr, int32_t ID, uintptr_t locationChanged)
{
	checkLocation(basicPtr, locationChanged);
	CGenericLogStorage::SaveFormattedTextLn("set_ID, basic 0x%X, value 0x%X location 0x%X", basicPtr, ID, locationChanged);
	CGenericLogStorage::SaveWorkBuffer();

	SetExtendedIDfrom16bitBefore(basicPtr, ID);
}

// 8-bit
F92_LA_API int32_t F92_LA_CONVENTION GetExtendedIDfrom8bitBefore(const void* basicPtr)
{
	int32_t* ptr = g_structureExtension.m_ID_extensionFrom8bit.GetPointerToExtendedData(basicPtr);

	if (ptr)
		return *ptr;
	else
	{
		uint8_t uID = *(uint8_t*)basicPtr;

		if (uID == 0xFF)	// is it unset ID?
			return -1;
		else
			return uID;
	}
}

F92_LA_API void F92_LA_CONVENTION SetExtendedIDfrom8bitBefore(void* basicPtr, int32_t ID)
{
	int32_t* ptr = g_structureExtension.m_ID_extensionFrom8bit.GetPointerToExtendedData(basicPtr);

	if (ptr)
	{
		*ptr = ID;

		if (!PROJECT_USE_DEVELOPMENT_INI)
			*(uint8_t*)basicPtr = ID;
	}
	else
		*(uint8_t*)basicPtr = ID;
}

void MarkExecuted(uintptr_t locationChanged)
{
	CGenericLogStorage::SaveFormattedTextLn("executed 0x%X", locationChanged);
	CGenericLogStorage::SaveWorkBuffer();
}

///////////////////////////////////////////////
namespace Patches
{
	uint16_t* GetPointerToBasicModelIDfieldInEntity(const CEntity* pEntity)
	{
		return (uint16_t*)((char*)pEntity + CEntity::m_wModelIndex.GetOffset());
	}

	extern "C"
	{
		void CEntity__constructor_extraCode(const CEntity* pEntity)
		{
			if (g_structureExtension.m_CEntityExtension.IsEnabled())
				New_CEntity(pEntity);

			const FileIDlimit* pFileIDlimits = &g_fileIDlimits;

			if (pFileIDlimits->bAreDifficultFileTypesInt32)
			{
				uint16_t* pBasicID = GetPointerToBasicModelIDfieldInEntity(pEntity);
				New_ID_from16bit(pBasicID);
			}

			if (pFileIDlimits->bIsIPLIDsizeIncreased)
				New_ID_from8bit((char*)pEntity + CEntity::m_nIplIndex.GetOffset());	// IPL ID		
		}

		void CEntity__destructor_extraCode(const CEntity* pEntity)
		{
			if (g_structureExtension.m_CEntityExtension.IsEnabled())
				Delete_CEntity(pEntity);

			const FileIDlimit* pFileIDlimits = &g_fileIDlimits;

			if (pFileIDlimits->bAreDifficultFileTypesInt32)
			{
				uint16_t* pBasicID = GetPointerToBasicModelIDfieldInEntity(pEntity);
				Delete_ID_from16bit(pBasicID);
			}

			if (pFileIDlimits->bIsIPLIDsizeIncreased)
				Delete_ID_from8bit((char*)pEntity + CEntity::m_nIplIndex.GetOffset());	// IPL ID
		}
	}

	// CEntity
	#ifdef IS_PLATFORM_WIN_X86
	NAKED void patch_CEntity__constructor()
	{
		__asm
		{
			push esi;
			call CEntity__constructor_extraCode;
			add esp, 4;

			mov dword ptr[esi + 0x1C], 8000080h; // dwFlags

			push 0x532AAC;
			retn;
		}
	}

	NAKED void patch_CEntity__destructor()
	{
		__asm
		{
			mov     fs:[0], ecx;

			push esi;
			call CEntity__destructor_extraCode;
			add esp, 4;

			pop esi;

			add     esp, 10h;
			retn;
		}
	}
	#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
	// patch for 0x3EAEFA
	extern "C"
	{
		uintptr_t Address_CEntity__CEntity_3EAF04_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CEntity__CEntity_3EAEFA()
	{
		__asm(
			".thumb\n"
			"MOV R0, R4\n"
			"BLX CEntity__constructor_extraCode\n"

			"LDR R0, =("/* _ZTV7CEntity_ptr */"0x676DD8 - 0x3EAF08)\n"
			"MOVS R1, #0x20\n"
			"STRB R1, [R4,#0x3A]\n"
			"MOVS R1, #0x80\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CEntity__CEntity_3EAF04_thumb)
			);
	}

	// patch for 0x3EAF2C
	static TARGET_THUMB NAKED void patch_CEntity__CEntity_3EAF2C()
	{
		__asm(
		".thumb\n"
			"MOV R0, R4\n"
			"BLX CEntity__destructor_extraCode\n"

			"STRH R5, [R4,#0x38]\n"
			"STR R5, [R4,#0x34]\n"
			"POP {R4,R5,R7,PC}\n"
			);
	}
	#endif

	extern "C"
	{
		// CObject
		void CObject__constructor_extraCode(const CObject_generic* pObject)
		{
			if (g_structureExtension.m_CObjectExtension.IsEnabled())
				New_CObject(pObject);

			if (g_fileIDlimits.bAreDifficultFileTypesInt32)
			{
				New_ID_from16bit((char*)pObject + 0x14A);	// m_nRefModelIndex
				New_ID_from16bit((char*)pObject + 0x16A);	// m_wRemapTxd
			}

			if (g_otherLimits.bIsVehicleColorIDextended)
			{
				New_ID_from8bit((char*)pObject + 0x14C);	// m_nVehiclePartPrimaryColor
				New_ID_from8bit((char*)pObject + 0x14D);	// m_nVehiclePartSecondaryColor
				New_ID_from8bit((char*)pObject + 0x14E);	// m_nVehiclePartTertiaryColor
				New_ID_from8bit((char*)pObject + 0x14F);	// m_nVehiclePartQuaternaryColor
			}

			if (g_weaponLimits.bWeaponIDsizeExtended)
				New_ID_from8bit((char*)pObject + 0x148);	// m_nLastWeaponDamageType
		}

		void CObject__destructor_extraCode(const CObject_generic* pObject)
		{
			if (g_fileIDlimits.bAreDifficultFileTypesInt32)
			{
				Delete_ID_from16bit((char*)pObject + 0x14A);	// m_nRefModelIndex
				Delete_ID_from16bit((char*)pObject + 0x16A);	// m_wRemapTxd
			}

			if (g_otherLimits.bIsVehicleColorIDextended)
			{
				Delete_ID_from8bit((char*)pObject + 0x14C);	// m_nVehiclePartPrimaryColor
				Delete_ID_from8bit((char*)pObject + 0x14D);	// m_nVehiclePartSecondaryColor
				Delete_ID_from8bit((char*)pObject + 0x14E);	// m_nVehiclePartTertiaryColor
				Delete_ID_from8bit((char*)pObject + 0x14F);	// m_nVehiclePartQuaternaryColor
			}

			if (g_weaponLimits.bWeaponIDsizeExtended)
				Delete_ID_from8bit((char*)pObject + 0x148);	// m_nLastWeaponDamageType

			if (g_structureExtension.m_CObjectExtension.IsEnabled())
				Delete_CObject(pObject);
		}
	}

	#ifdef IS_PLATFORM_WIN_X86
	NAKED void patch_CObject__Create_5A1FA1()
	{
		__asm
		{
			push 0;	// bCreate
			push edi;	// modelID
			mov ecx, esi;	// this

			push continueTheCode;
			push 0x5A1D70;	// CObject::CObject(CObject *this, int modelID, char a3)
			retn;

		continueTheCode:
			mov     eax, esi;

			push 0x5A1FCE;
			retn;
		}
	}
	
	NAKED void patch_CObject__Create_5A2016()
	{
		__asm
		{
			push 0;	// bCreate
			push edi;	// modelID
			mov ecx, esi;	// this

			push 0x5A203D;	// go back
			push 0x5A1D70;	// CObject::CObject(CObject *this, int modelID, char a3)
			retn;
		}
	}

	NAKED void patch_CObject_constructor_5A1D32()
	{
		__asm
		{
			push esi;
			call CObject__constructor_extraCode;
			add esp, 4;

			mov     ecx, esi;
			mov[esp + 14h - 4], 0;
			push 0x5A1D3C;
			retn;
		}
	}

	NAKED void patch_CObject_advanced_constructor_5A1D92()
	{
		__asm
		{
			push esi;
			call CObject__constructor_extraCode;
			add esp, 4;

			mov     cl, [esp + 14h + 8];
			xor eax, eax;

			push 0x5A1D98;
			retn;
		}
	}

	NAKED void patch_CObject_constructor_fromDummy()
	{
		__asm
		{
			push esi;
			call CObject__constructor_extraCode;
			add esp, 4;

			mov ecx, edi;
			call CEntity::GetModelID;
			push eax;

			push 0x5A1E22;
			retn;
		}
	}

	NAKED void patch_CObject_destructor()
	{
		__asm
		{
			mov     fs:[0], ecx;

			push esi;
			call CObject__destructor_extraCode;
			add esp, 4;

			pop esi;

			add     esp, 1Ch;
			retn;
		}
	}
	#endif

	extern "C"
	{
		// CColModel
		void CColModel__constructor_extraCode(const CColModel_generic* pObject)
		{
			if (g_structureExtension.m_CColModelExtension.IsEnabled())
				New_CColModel(pObject);

			if (g_fileIDlimits.bIsCOLIDsizeIncreased)
				*New_ID_from8bit(&((Game_GTASA::CColModel*)pObject)->COL_file_ID) = 0;
		}

		void CColModel__destructor_extraCode(const CColModel_generic* pObject)
		{
			if (g_fileIDlimits.bIsCOLIDsizeIncreased)
				Delete_ID_from8bit(&((Game_GTASA::CColModel*)pObject)->COL_file_ID);

			if (g_structureExtension.m_CColModelExtension.IsEnabled())
				Delete_CColModel(pObject);
		}
	}

	#ifdef IS_PLATFORM_WIN_X86
	NAKED void patch_CColModel_constructor()
	{
		__asm
		{
			push esi;
			call CColModel__constructor_extraCode;
			add esp, 4;

			mov eax, esi;
			pop esi;
			retn;
		}
	}

	NAKED void patch_CColModel_destructor()
	{
		__asm
		{
			push esi;
			call CColModel__destructor_extraCode;
			add esp, 4;

			pop esi;
			retn;
		}
	}
	#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
	static TARGET_THUMB NAKED void patch_CColModel__CColModel_2E1742()
	{
		__asm(
			".thumb\n"
			"AND R1, R1, #0xF8\n"
			"STRB R1, [R0,#0x29]\n"

			"B CColModel__constructor_extraCode\n"
			);
	}

	// patch for 0x2E17CC
	extern "C"
	{
		uintptr_t Address_CColModel___CColModel_193D34_arm = 0;
		uintptr_t Address_CColModel___CColModel_2E17D4_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CColModel___CColModel_2E17CC()
	{
		__asm(
			".thumb\n"
			"BL 1f\n"

			"MOV R0, R4\n"
			"BLX CColModel__destructor_extraCode\n"

			"MOV R0, R4\n"
			"POP {R4,R6,R7,PC}\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CColModel___CColModel_2E17D4_thumb)

			// Branches
			"1:\n"	// j__ZN10CMemoryMgr4FreeEPv
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CColModel___CColModel_193D34_arm)
			);
	}
	#endif

	extern "C"
	{
		// CVehicle
		void CAutopilot__constructor_extraCode(const void* pAutoPilot)
		{
			g_structureExtension.m_CLinkAddress_extension.New(
				(char*)pAutoPilot + 0x14);	// m_wCurrentPathNodeInfo
			g_structureExtension.m_CLinkAddress_extension.New(
				(char*)pAutoPilot + 0x16);	// m_wNextPathNodeInfo
			g_structureExtension.m_CLinkAddress_extension.New(
				(char*)pAutoPilot + 0x18);	// m_wPreviousPathNodeInfo
		}

		void CAutopilot__destructor_extraCode(const void* pAutoPilot)
		{
			g_structureExtension.m_CLinkAddress_extension.Delete(
				(char*)pAutoPilot + 0x14);	// m_wCurrentPathNodeInfo
			g_structureExtension.m_CLinkAddress_extension.Delete(
				(char*)pAutoPilot + 0x16);	// m_wNextPathNodeInfo
			g_structureExtension.m_CLinkAddress_extension.Delete(
				(char*)pAutoPilot + 0x18);	// m_wPreviousPathNodeInfo
		}
	}

	#ifdef IS_PLATFORM_WIN_X86
	NAKED void patch_CAutoPilot_constructor()
	{
		__asm
		{
			mov eax, 0x4F63E0;	// _ZN21CAEVehicleAudioEntityC2Ev
			call eax;

			lea ecx, dword ptr[esi + (/* CVehicle */0x0 + /* m_Autopilot */0x390)];

			push ecx;
			call CAutopilot__constructor_extraCode;
			add esp, 4;

			ASM_JMP_STATIC_ADDRESS(0x6D5F4B);
		}
	}

	NAKED void patch_CAutoPilot_destructor()
	{
		__asm
		{
			lea ecx, dword ptr[esi + (/* CVehicle */0x0 + /* m_Autopilot */0x390)];

			push ecx;
			call CAutopilot__destructor_extraCode;
			add esp, 4;

			mov ecx, dword ptr[esp + 10h];
			pop edi;

			ASM_JMP_STATIC_ADDRESS(0x6E2D3F);
		}
	}
	#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
	// patch for 0x581652, constructor
	extern "C"
	{
		uintptr_t Address_CVehicle__CVehicle_191DBC_arm = 0;	// j__ZN21CAEVehicleAudioEntityC2Ev
		uintptr_t Address_CVehicle__CVehicle_58165C_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CVehicle__CVehicle_581652()
	{
		__asm(
			".thumb\n"
			"BL 1f\n"

			"ADD R0, R4, #0x394\n"
			"BLX CAutopilot__constructor_extraCode\n"

			"LDR R0, =("/* _ZN6CTimer22m_snTimeInMillisecondsE_ptr */"0x676FFC - 0x581666)\n"
			"MOV R1, #0xFFFF\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CVehicle__CVehicle_58165C_thumb)

			// Branches
			"1:\n"	// j__ZN21CAEVehicleAudioEntityC2Ev
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CVehicle__CVehicle_191DBC_arm)
			);
	}

	// patch for 0x581B8E, destructor
	extern "C"
	{
		uintptr_t Address_CVehicle___CVehicle_19446C_thumb = 0;	// sub_19446C
	}

	static TARGET_THUMB NAKED void patch_CVehicle___CVehicle_581B8E()
	{
		__asm(
		".thumb\n"
			"ADD R0, R4, #0x394\n"
			"BLX CAutopilot__destructor_extraCode\n"

			"MOV R0, R4\n"
			"POP {R4,R5,R7,LR}\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CVehicle___CVehicle_19446C_thumb)
			);
	}
	#endif

	extern "C"
	{
		// CVehicle
		void CVehicle__constructor_extraCode(const CVehicle_generic* pVehicle)
		{
			if (g_structureExtension.m_CVehicleExtension.IsEnabled())
				New_CVehicle(pVehicle);

			if (g_fileIDlimits.bAreDifficultFileTypesInt32)
			{
				New_ID_from16bit((char*)pVehicle + 0x598);	// m_wPreviousRemapTxd
				New_ID_from16bit((char*)pVehicle + 0x59A);	// m_wRemapTxd
			}

			if (g_weaponLimits.bWeaponIDsizeExtended)
				New_ID_from8bit((char*)pVehicle + 0x508);	// m_nLastWeaponDamageType

			if (g_otherLimits.bIsVehicleColorIDextended)
			{
				New_ID_from8bit((char*)pVehicle + 0x434);	// m_nPrimaryColor
				New_ID_from8bit((char*)pVehicle + 0x435);	// m_nSecondaryColor
				New_ID_from8bit((char*)pVehicle + 0x436);	// m_nTertiaryColor
				New_ID_from8bit((char*)pVehicle + 0x437);	// m_nQuaternaryColor
			}
		}

		void CVehicle__destructor_extraCode(const CVehicle_generic* pVehicle)
		{
			if (g_fileIDlimits.bAreDifficultFileTypesInt32)
			{
				Delete_ID_from16bit((char*)pVehicle + 0x598);	// m_wPreviousRemapTxd
				Delete_ID_from16bit((char*)pVehicle + 0x59A);	// m_wRemapTxd
			}

			if (g_weaponLimits.bWeaponIDsizeExtended)
				Delete_ID_from8bit((char*)pVehicle + 0x508);	// m_nLastWeaponDamageType

			if (g_otherLimits.bIsVehicleColorIDextended)
			{
				Delete_ID_from8bit((char*)pVehicle + 0x434);	// m_nPrimaryColor
				Delete_ID_from8bit((char*)pVehicle + 0x435);	// m_nSecondaryColor
				Delete_ID_from8bit((char*)pVehicle + 0x436);	// m_nTertiaryColor
				Delete_ID_from8bit((char*)pVehicle + 0x437);	// m_nQuaternaryColor
			}

			if (g_structureExtension.m_CVehicleExtension.IsEnabled())
				Delete_CVehicle(pVehicle);
		}
	}

	#ifdef IS_PLATFORM_WIN_X86
	NAKED void patch_CVehicle_constructor()
	{
		__asm
		{
			push ecx;

			push esi;
			call CVehicle__constructor_extraCode;
			add esp, 4;

			pop ecx;
			
			mov[esp + 1Ch - 4], ebx;
			mov[esi], 0x871E80;	// VTBL_CVehicle

			push 0x6D5F46;
			retn;
		}
	}

	NAKED void patch_CVehicle_destructor()
	{
		__asm
		{
			mov     fs:[0], ecx;

			push esi;
			call CVehicle__destructor_extraCode;
			add esp, 4;

			pop esi;
			pop ebx;
			
			add esp, 10h;
			retn;
		}
	}
	#endif

	extern "C"
	{
		// CPed
		void CPed__constructor_extraCode(const CPed_generic* pPed)
		{
			if (g_weaponLimits.bWeaponIDsizeExtended)
				New_ID_from8bit((char*)pPed + 0x760);	// m_nLastWeaponDamageType
		}

		void CPed__destructor_extraCode(const CPed_generic* pPed)
		{
			if (g_weaponLimits.bWeaponIDsizeExtended)
				Delete_ID_from8bit((char*)pPed + 0x760);	// m_nLastWeaponDamageType
		}
	}

	#ifdef IS_PLATFORM_WIN_X86
	NAKED void patch_CPed_constructor()
	{
		__asm
		{

			push esi;
			call CPed__constructor_extraCode;
			add esp, 4;

			lea ebp, [esi + 0x138];

			push 0x5E805D;
			retn;
		}
	}

	NAKED void patch_CPed_destructor()
	{
		__asm
		{
			mov     fs:[0], ecx;

			push esi;
			call CPed__destructor_extraCode;
			add esp, 4;

			pop esi;
			pop ebp;
			pop ebx;
			
			add esp, 14h;
			retn;
		}
	}
	#endif

	extern "C"
	{
		// TxdDef
		void TxdDef__constructor_extraCode(const TxdDef_generic* pTxd)
		{
			if (g_fileIDlimits.bAreDifficultFileTypesInt32)
				New_ID_from16bit(&((Game_GTASA::TxdDef*)pTxd)->parent_index);
		}

		void TxdDef__destructor_extraCode(const TxdDef_generic* pTxd)
		{
			if (g_fileIDlimits.bAreDifficultFileTypesInt32)
				Delete_ID_from16bit(&((Game_GTASA::TxdDef*)pTxd)->parent_index);
		}
	}

	#ifdef IS_PLATFORM_WIN_X86
	NAKED void patch_CTxdStore__Initialise_731F92()
	{
		__asm
		{
			push esi;
			call TxdDef__constructor_extraCode;
			add esp, 4;

			mov dword ptr[esi + Game_GTASA::TxdDef::dictionary], 0;
			push 0x731F98;
			retn;
		}
	}

	NAKED void patch_CTxdStore__AddTxdSlot_731C93()
	{
		__asm
		{
			push esi;
			call TxdDef__constructor_extraCode;
			add esp, 4;

			mov dword ptr[esi + Game_GTASA::TxdDef::dictionary], 0;
			push 0x731C99;
			retn;
		}
	}

	static NAKED void patch_CTxdStore__RemoveTxdSlot_731CF1()
	{
		__asm
		{
			mov edx, eax;
			mov     eax, [eax];
			test    eax, eax;
			jz loc_731D06;

			mov dword ptr[edx], 0xFACED123;

			push 0x731CF7;
			retn;

		loc_731D06:
			push 0x731D06;
			retn;
		}
	}

	NAKED void patch_CTxdStore__RemoveTxdSlot_731D1B()
	{
		__asm
		{
			push ecx;
			push eax;

			push eax;
			call TxdDef__destructor_extraCode;
			add esp, 4;

			pop eax;
			pop ecx;

			sub     eax, [ecx + CPool_GTASA_void::m_pObjects];

			mov     edx, eax;
			mov     eax, 2AAAAAABh;

			push 0x731D24;
			retn;
		}
	}
	#endif

	extern "C"
	{
		void CTxdStore__DestructElements()
		{
			const FileIDlimit* pFileIDlimits = &g_fileIDlimits;
			tFileTypeLimit txdLimit = pFileIDlimits->GetFileIDcurrentLimit(GENERAL_FILE_TYPE_TEXTURE_ARCHIVE);

			CPool_GTASA<Game_GTASA::TxdDef>* pPool = ACCESS_DEF(pFileIDlimits->CTxdStore__pTxdPool.gta_sa);

			for (tFileTypeLimit ID = 0; ID < txdLimit; ID++)
			{
				auto pElement = pPool->GetAt(ID);

				if (pElement)
					TxdDef__destructor_extraCode(pElement);

				// if (!pPool->IsFreeSlotAtIndex(ID))
					// TxdDef__destructor_extraCode()
					/*
					((void(__cdecl *)(int))0x731CD0)(
						ID
						);		// CTxdStore::RemoveTxdSlot
						*/
			}
		}
	}

	#ifdef IS_PLATFORM_WIN_X86
	NAKED void patch_CTxdStore__Shutdown_732000()
	{
		__asm
		{
			call CTxdStore__DestructElements;

			mov eax, ASM_ACCESS_LIMIT_VAR_32_BIT(g_fileIDlimits, FileIDlimit, CTxdStore__pTxdPool);
			mov eax, [eax];

			push 0x732005;
			retn;
		}
	}

	NAKED void patch_CGame__Init1_5BF845()
	{
		__asm
		{
			push goBack;
			push 0x731F20;
			retn;

			goBack:
			mov eax, [esp + 4];
			push 0x5BF849;
			retn;
		}
	}
	#endif

	extern "C"
	{
		// CIplFile
		void CIplFile__constructor_extraCode(const CIplFile_generic* pFile)
		{
			MAKE_VAR_GAME_VERSION();

			if (g_fileIDlimits.bAreDifficultFileTypesInt32)
			{
				if (CGameVersion::IsAny_GTA_SA(gameVersion))
				{
					auto pFileX = (Game_GTASA::CIplFile*)pFile;
					New_ID_from16bit(&pFileX->m_usBuildingsBegin);
					New_ID_from16bit(&pFileX->m_usBuildingsEnd);
					New_ID_from16bit(&pFileX->m_usDummyBegin);
					New_ID_from16bit(&pFileX->m_usDummyEnd);
				}
			}
		}

		void CIplFile__destructor_extraCode(const CIplFile_generic* pFile)
		{
			MAKE_VAR_GAME_VERSION();

			if (g_fileIDlimits.bAreDifficultFileTypesInt32)
			{
				if (CGameVersion::IsAny_GTA_SA(gameVersion))
				{
					auto pFileX = (Game_GTASA::CIplFile*)pFile;
					Delete_ID_from16bit(&pFileX->m_usBuildingsBegin);
					Delete_ID_from16bit(&pFileX->m_usBuildingsEnd);
					Delete_ID_from16bit(&pFileX->m_usDummyBegin);
					Delete_ID_from16bit(&pFileX->m_usDummyEnd);
				}
			}
		}
	}

	#ifdef IS_PLATFORM_WIN_X86
	uintptr_t Address_405AD2 = 0;

	NAKED void patch_CIplStore__AddIplSlot_405ACD()
	{
		__asm
		{
			push eax;

			push eax;
			call CIplFile__constructor_extraCode;
			add esp, 4;

			pop eax;

			mov     ecx, -1000000.0;

			jmp Address_405AD2;
		}
	}

	uintptr_t Address_405BDB = 0;

	NAKED void patch_CIplStore__RemoveIplSlot_405BD4()
	{
		__asm
		{
			push ecx;

			push esi;
			call CIplFile__destructor_extraCode;
			add esp, 4;

			pop ecx;

			sub     esi, [ecx + CPool_GTASA_void::m_pObjects];
			mov     eax, 4EC4EC4Fh;

			jmp Address_405BDB;
		}
	}
	#endif

	extern "C"
	{
		// CColisionFile
		void CCollisionFile__constructor_extraCode(const CCollisionFile_generic* pFile)
		{
			MAKE_VAR_GAME_VERSION();

			if (g_fileIDlimits.bAreDifficultFileTypesInt32)
			{
				if (CGameVersion::IsAny_GTA_SA(gameVersion))
				{
					auto pFileX = (Game_GTASA::CCollisionFile*)pFile;

					New_ID_from16bit(&pFileX->m_wLowestModelID);
					New_ID_from16bit(&pFileX->m_wHighestModelID);
				}
			}
		}

		void CCollisionFile__destructor_extraCode(const CCollisionFile_generic* pFile)
		{
			MAKE_VAR_GAME_VERSION();

			if (g_fileIDlimits.bAreDifficultFileTypesInt32)
			{
				if (CGameVersion::IsAny_GTA_SA(gameVersion))
				{
					auto pFileX = (Game_GTASA::CCollisionFile*)pFile;
					Delete_ID_from16bit(&pFileX->m_wLowestModelID);
					Delete_ID_from16bit(&pFileX->m_wHighestModelID);
				}
			}
		}
	}

	#ifdef IS_PLATFORM_WIN_X86
	uintptr_t Address_CColStore__AddColSlot_pointToReturn = 0;

	NAKED void patch_CColStore__AddColSlot_411153()
	{
		__asm
		{
			push esi;
			call CCollisionFile__constructor_extraCode;
			add esp, 4;

			xor eax, eax;
			mov     ecx, -1000000.0;
			jmp Address_CColStore__AddColSlot_pointToReturn;
		}
	}

	uintptr_t Address_4113AB;

	NAKED void patch_CColStore__RemoveColSlot_4113A4()
	{
		__asm
		{
			push ecx;

			push esi;
			call CCollisionFile__destructor_extraCode;
			add esp, 4;

			pop ecx;

			sub     esi, [ecx + CPool_GTASA_void::m_pObjects];
			mov     eax, 2E8BA2E9h;
			jmp Address_4113AB;
		}
	}
	#endif

	extern "C"
	{
		// atomic
		uint32_t* CVisibilityPlugins__ms_atomicPluginOffset = (uint32_t*)0x8D608C;

		void* CVisibilityPlugins__AtomicConstructor(void *object, int offsetInObject, int sizeInObject)
		{
			char* pAtomic = (char*)object + *CVisibilityPlugins__ms_atomicPluginOffset;

			if (g_fileIDlimits.bAreDifficultFileTypesInt32)
				*New_ID_from16bit(pAtomic) = -1;

			*(uint16_t*)(pAtomic) = 0xFFFF;
			*(uint16_t*)(pAtomic + 2) = 0;
			return object;
		}

		void* CVisibilityPlugins__AtomicDestructor(void *object, int offsetInObject, int sizeInObject)
		{
			const char* pAtomic = (char*)object + *CVisibilityPlugins__ms_atomicPluginOffset;

			if (g_fileIDlimits.bAreDifficultFileTypesInt32)
				Delete_ID_from16bit(pAtomic);

			return object;
		}

		// CTimeModelInfo
		void CTimeModelInfo__constructor_extraCode(const void* pObject)
		{
			if (g_fileIDlimits.bAreDifficultFileTypesInt32)
				New_ID_from16bit((char*)pObject + 0x22);	// m_timeInfo.m_wOtherTimeModel
		}

		void CTimeModelInfo__destructor_extraCode(const void* pObject)
		{
			if (g_fileIDlimits.bAreDifficultFileTypesInt32)
				Delete_ID_from16bit((char*)pObject + 0x22);	// m_timeInfo.m_wOtherTimeModel
		}
	}

	#ifdef IS_PLATFORM_WIN_X86
	NAKED void patch_CTimeModelInfo__constructor_4C564E()
	{
		__asm
		{
			push esi;
			call CTimeModelInfo__constructor_extraCode;
			add esp, 4;

			push UNDEFINED_FILE_ID_INT32;
			lea eax, [esi + 20h + 2];	// CTimeModelInfo.m_timeInfo.m_wOtherTimeModel
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;

			mov eax, esi;
			pop esi;
			retn;
		}
	}

	NAKED void patch_CTimeModelInfo__destructor_4C5686()
	{
		__asm
		{
			push ecx;
			call CTimeModelInfo__destructor_extraCode;
			add esp, 4;
			retn;
		}
	}
	#endif

	extern "C"
	{
		// CLodTimeModelInfo
		void CLodTimeModelInfo__constructor_extraCode(const void* pObject)
		{
			if (g_fileIDlimits.bAreDifficultFileTypesInt32)
				New_ID_from16bit((char*)pObject + 0x26);	// m_timeInfo.m_wOtherTimeModel
		}

		void CLodTimeModelInfo__destructor_extraCode(const void* pObject)
		{
			if (g_fileIDlimits.bAreDifficultFileTypesInt32)
				Delete_ID_from16bit((char*)pObject + 0x26);	// m_timeInfo.m_wOtherTimeModel
		}
	}

	#ifdef IS_PLATFORM_WIN_X86
	NAKED void patch_CLodTimeModelInfo__constructor_4C56A8()
	{
		__asm
		{
			push esi;
			call CLodTimeModelInfo__constructor_extraCode;
			add esp, 4;

			push UNDEFINED_FILE_ID_INT32;
			lea eax, [esi + 26h];	// CLodTimeModelInfo.m_timeInfo.m_wOtherTimeModel
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;

			mov eax, esi;
			pop esi;
			retn;
		}
	}
	#endif

	extern "C"
	{
		// CVehicleModelInfo
		void CVehicleModelInfo__constructor_extraCode(const void* pObject)
		{
			uint16_t* pOriginalRemapArray = (uint16_t*)((char*)pObject + 0x2FA);

			if (g_fileIDlimits.bAreDifficultFileTypesInt32)
				for (int i = 0; i < 4; i++)
					New_ID_from16bit(pOriginalRemapArray + i);

			if (g_otherLimits.bIsVehicleColorIDextended)
			{
				for (int i = 0; i < 8; i++)
				{
					New_ID_from8bit((char*)pObject + 0x2B0 + i);	// m_anPrimaryColors
					New_ID_from8bit((char*)pObject + 0x2B8 + i);	// m_anSecondaryColors
					New_ID_from8bit((char*)pObject + 0x2C0 + i);	// m_anTertiaryColors
					New_ID_from8bit((char*)pObject + 0x2C8 + i);	// m_anQuaternaryColors
				}

				New_ID_from8bit((char*)pObject + 0x2D2);	// m_nCurrentPrimaryColor
				New_ID_from8bit((char*)pObject + 0x2D3);	// m_nCurrentSecondaryColor
				New_ID_from8bit((char*)pObject + 0x2D4);	// m_nCurrentTertiaryColor
				New_ID_from8bit((char*)pObject + 0x2D5);	// m_nCurrentQuaternaryColor
			}
		}

		void CVehicleModelInfo__destructor_extraCode(const void* pObject)
		{
			uint16_t* pOriginalRemapArray = (uint16_t*)((char*)pObject + 0x2FA);

			if (g_fileIDlimits.bAreDifficultFileTypesInt32)
				for (int i = 0; i < 4; i++)
					Delete_ID_from16bit(pOriginalRemapArray + i);

			if (g_otherLimits.bIsVehicleColorIDextended)
			{
				for (int i = 0; i < 8; i++)
				{
					Delete_ID_from8bit((char*)pObject + 0x2B0 + i);	// m_anPrimaryColors
					Delete_ID_from8bit((char*)pObject + 0x2B8 + i);	// m_anSecondaryColors
					Delete_ID_from8bit((char*)pObject + 0x2C0 + i);	// m_anTertiaryColors
					Delete_ID_from8bit((char*)pObject + 0x2C8 + i);	// m_anQuaternaryColors
				}

				Delete_ID_from8bit((char*)pObject + 0x2D2);	// m_nCurrentPrimaryColor
				Delete_ID_from8bit((char*)pObject + 0x2D3);	// m_nCurrentSecondaryColor
				Delete_ID_from8bit((char*)pObject + 0x2D4);	// m_nCurrentTertiaryColor
				Delete_ID_from8bit((char*)pObject + 0x2D5);	// m_nCurrentQuaternaryColor
			}
		}
	}

	#ifdef IS_PLATFORM_WIN_X86
	NAKED void patch_CVehicleModelInfo__constructor_4C75E9()
	{
		__asm
		{
			push esi;
			call CVehicleModelInfo__constructor_extraCode;
			add esp, 4;

			xor     eax, eax;
			mov[esi + 5Ch], eax;	// CVehicleModelInfo.m_pVehicleStruct
			push 0x4C75EE;
			retn;
		}
	}
	#endif

	extern "C"
	{
		// CBaseModelInfo
		void CBaseModelInfo__constructor_extraCode(const void* pObject)
		{
			if (g_fileIDlimits.bAreDifficultFileTypesInt32)
			{
				New_ID_from16bit((char*)pObject + 0xA);	// m_wTxdIndex
				// New_ID_from16bit((char*)pObject + 0xE);	// m_n2dEffectIndex
			}
		}

		void CBaseModelInfo__destructor_extraCode(const void* pObject)
		{
			if (g_fileIDlimits.bAreDifficultFileTypesInt32)
			{
				Delete_ID_from16bit((char*)pObject + 0xA);	// m_wTxdIndex
				// Delete_ID_from16bit((char*)pObject + 0xE);	// m_n2dEffectIndex
			}
		}
	}

	static const uintptr_t Address_CBaseModelInfo_destructor = 0x4C5510;

	#ifdef IS_PLATFORM_WIN_X86
	NAKED void patch_CBaseModelInfo_constructor_4C4A68()
	{
		__asm
		{
			push eax;

			push eax;
			call CBaseModelInfo__constructor_extraCode;
			add esp, 4;

			pop eax;

			mov word ptr[eax + 8], 0;	// CBaseModelInfo.m_wUsageCount

			push 0x4C4A6E;
			retn;
		}
	}

	NAKED void patch_CBaseModelInfo__scalarDestructor_4C4AF8()
	{
		__asm
		{
			push 0x4C4AFE;	// go back
			
			push Address_CBaseModelInfo_destructor;	// CBaseModelInfo::~CBaseModelInfo()
			retn;
		}
	}

	NAKED void patch_CPedModelInfo__scalarDestructor_4C6333()
	{
		_asm
		{			
			mov ecx, esi;
			call Address_CBaseModelInfo_destructor;

			mov     ecx, [esp + 18h - 0xC];
			pop     edi;
			pop esi;
			mov     fs:[0], ecx;
			add     esp, 10h;
			retn;
		}
	}

	void NAKED patch_CBaseModelInfo__destructor_4C5516()
	{
		__asm
		{
			push ecx;
			call CBaseModelInfo__constructor_extraCode;
			add esp, 4;
			retn;
		}
	}
	#endif

	template <void(*func)(const void* pObject)> class CBaseModelInfo_x12234
	{
	public:
		void Destructor()
		{
			func(this);

			((void(__thiscall*)(CBaseModelInfo_x12234*))Address_CBaseModelInfo_destructor)(this);
		}
	};

	extern "C"
	{
		// Furniture_c
		void Furniture_c__constructor_extraCode(const Game_GTASA::Furniture_c* pObject)
		{
			if (g_fileIDlimits.bAreDifficultFileTypesInt32)
				New_ID_from16bit(&pObject->m_wModelIndex);	// m_wModelIndex
		}

		void Furniture_c__destructor_extraCode(const Game_GTASA::Furniture_c* pObject)
		{
			if (g_fileIDlimits.bAreDifficultFileTypesInt32)
				Delete_ID_from16bit(&pObject->m_wModelIndex);	// m_wModelIndex
		}
	}

	#ifdef IS_PLATFORM_WIN_X86
	NAKED void patch_Furniture_c__constructor_590EC8()
	{
		__asm
		{
			push esi;
			call Furniture_c__constructor_extraCode;
			add esp, 4;

			mov eax, esi;
			pop esi;
			retn;
		}
	}
	#endif

	struct Furniture_c_535353
	{
		void destructor()
		{
			Furniture_c__destructor_extraCode((const Game_GTASA::Furniture_c*)this);

			((void(__thiscall*)(Furniture_c_535353*))0x4A8DC0)(this);	// ListItem_c::~ListItem_c
		}
	};
}


// Processes
void StructureExtension::ApplyHook()
{
	MAKE_VAR_GAME_VERSION();

	const FileIDlimit* pFileIDlimits = &g_fileIDlimits;
	const OtherLimits* pOtherLimits = &g_otherLimits;

	CStreaming__ms_aInfoForModel_start = pFileIDlimits->CStreaming__ms_aInfoForModel.gta_sa;
	CStreaming__ms_aInfoForModel_end = CStreaming__ms_aInfoForModel_start + pFileIDlimits->GetCountOfAllFileIDs();

	CPatch::EnterNewLevel();

	using namespace Patches;
		
	// CEntity
	if (this->m_CEntityExtension.IsEnabled()
		|| pFileIDlimits->bAreDifficultFileTypesInt32
		|| pFileIDlimits->bIsIPLIDsizeIncreased)
	{
		#ifdef IS_PLATFORM_WIN_X86
		if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		{
			CPatch::RedirectCode(0x532AA5, &patch_CEntity__constructor);
			CPatch::RedirectCode(0x535EE6, &patch_CEntity__destructor);
		}
		#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
		if(gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
		{
			// constructor
			Address_CEntity__CEntity_3EAF04_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x3EAF04));
			CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x3EAEFA),
				(void*)&patch_CEntity__CEntity_3EAEFA
			);

			// destructor
			CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x3EAF2C),
				(void*)&patch_CEntity__CEntity_3EAF2C
			);
		}
		#endif
	}

	// CObject
	if (this->m_CObjectExtension.IsEnabled()
		|| g_weaponLimits.bWeaponIDsizeExtended
		|| pFileIDlimits->bAreDifficultFileTypesInt32
		|| pOtherLimits->bIsVehicleColorIDextended)
	{
		#ifdef IS_PLATFORM_WIN_X86
		if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		{
			CPatch::RedirectCode(0x5A1D32, &patch_CObject_constructor_5A1D32);

			CPatch::RedirectCode(0x5A1D92, &patch_CObject_advanced_constructor_5A1D92);

			CPatch::RedirectCode(0x5A1E1D, &patch_CObject_constructor_fromDummy);
			CPatch::RedirectCode(0x59F834, &patch_CObject_destructor);

			CPatch::RedirectCode(0x5A1FA1, &patch_CObject__Create_5A1FA1);
			CPatch::RedirectCode(0x5A2016, &patch_CObject__Create_5A2016);
		}
		#endif
	}

	// CColModel
	if (this->m_CColModelExtension.IsEnabled()
		|| pFileIDlimits->bIsCOLIDsizeIncreased)
	{
		#ifdef IS_PLATFORM_WIN_X86
		if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		{
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_COMPACT_WIN_X86)
				CPatch::RedirectCode(0x40FB7A, &patch_CColModel_constructor);
			else if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
				CPatch::RedirectCode(0x156C6AA, &patch_CColModel_constructor);

			CPatch::RedirectCode(0x40F73A, &patch_CColModel_destructor);
		}
		#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
		if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
		{
			CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x2E1742),
				(void*)&patch_CColModel__CColModel_2E1742
			);

			Address_CColModel___CColModel_193D34_arm = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_ARM_ADDRESS_FOR_JUMP(0x193D34));
			Address_CColModel___CColModel_2E17D4_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2E17D4));
			CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x2E17CC),
				(void*)&patch_CColModel___CColModel_2E17CC
			);
		}
		#endif
	}

	// CVehicle
	if (this->m_CVehicleExtension.IsEnabled() || pFileIDlimits->bAreDifficultFileTypesInt32
		|| g_weaponLimits.bWeaponIDsizeExtended
		|| pOtherLimits->bIsVehicleColorIDextended)
	{
		#ifdef IS_PLATFORM_WIN_X86
		if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		{
			CPatch::RedirectCode(0x6D5F3C, &patch_CVehicle_constructor);
			CPatch::RedirectCode(0x6E2D3F, &patch_CVehicle_destructor);
		}
		#endif
	}

	// CAutopilot
	if (this->m_CLinkAddress_extension.IsEnabled())
	{
		#ifdef IS_PLATFORM_WIN_X86
		if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		{
			CPatch::RedirectCode(0x6D5F46, &patch_CAutoPilot_constructor);
			CPatch::RedirectCode(0x6E2D3A, &patch_CAutoPilot_destructor);
		}
		#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
		if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
		{
			// Constructor
			Address_CVehicle__CVehicle_191DBC_arm = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_ARM_ADDRESS_FOR_JUMP(0x191DBC));
			Address_CVehicle__CVehicle_58165C_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x58165C));
			CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x581652),
				(void*)&patch_CVehicle__CVehicle_581652
			);

			// Destructor
			Address_CVehicle___CVehicle_19446C_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x19446C));
			CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x581B8E),
				(void*)&patch_CVehicle___CVehicle_581B8E
			);			
		}
		#endif
	}

	// CPed
	if (g_weaponLimits.bWeaponIDsizeExtended)
	{
		#ifdef IS_PLATFORM_WIN_X86
		if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		{
			CPatch::RedirectCode(0x5E8057, &patch_CPed_constructor);
			CPatch::RedirectCode(0x5E8816, &patch_CPed_destructor);
		}
		#endif
	}
		
	// TxdDef
	if (pFileIDlimits->bAreDifficultFileTypesInt32)
	{
		#ifdef IS_PLATFORM_WIN_X86
		if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		{
			// _defaultTxds
			for (int i = 0; i < 4; i++)
				New_ID_from16bit((uint16_t*)0xC88004 + i);

			CPatch::RedirectCode(0x731F92, &patch_CTxdStore__Initialise_731F92);
			CPatch::RedirectCode(0x731C93, &patch_CTxdStore__AddTxdSlot_731C93);

			// CPatch::RedirectCode(0x731CF1, &patch_CTxdStore__RemoveTxdSlot_731CF1);
			CPatch::RedirectCode(0x731D1B, &patch_CTxdStore__RemoveTxdSlot_731D1B);

			// CPatch::RedirectCode(0x732000, &patch_CTxdStore__Shutdown_732000);
		}
		#endif
	}
		
	// CIplFile
	if (pFileIDlimits->bAreDifficultFileTypesInt32)
	{
		#ifdef IS_PLATFORM_WIN_X86
		if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_COMPACT_WIN_X86)
		{
			Address_405AD2 = 0x405AD2;
			Address_405BDB = 0x405BDB;
			CPatch::RedirectCode(0x405ACD, &patch_CIplStore__AddIplSlot_405ACD);
			CPatch::RedirectCode(0x405BD4, &patch_CIplStore__RemoveIplSlot_405BD4);
		}
		else if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
		{
			Address_405AD2 = 0x156C482;
			Address_405BDB = 0x156C66B;
			CPatch::RedirectCode(0x156C47D, &patch_CIplStore__AddIplSlot_405ACD);
			CPatch::RedirectCode(0x156C664, &patch_CIplStore__RemoveIplSlot_405BD4);
		}			
		#endif
	}

	// CColisionFile
	if (pFileIDlimits->bAreDifficultFileTypesInt32)
	{
		#ifdef IS_PLATFORM_WIN_X86
		if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_COMPACT_WIN_X86)
		{
			Address_CColStore__AddColSlot_pointToReturn = 0x41115A;
			CPatch::RedirectCode(0x411153, &patch_CColStore__AddColSlot_411153);

			Address_4113AB = 0x4113AB;
			CPatch::RedirectCode(0x4113A4, &patch_CColStore__RemoveColSlot_4113A4);
		}
		else if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
		{
			Address_CColStore__AddColSlot_pointToReturn = 0x15632AA;
			CPatch::RedirectCode(0x15632A3, &patch_CColStore__AddColSlot_411153);

			Address_4113AB = 0x156728B;
			CPatch::RedirectCode(0x1567284, &patch_CColStore__RemoveColSlot_4113A4);
		}
		#endif
	}

	// RW atomic
	if (pFileIDlimits->bAreDifficultFileTypesInt32)
	{
		#ifdef IS_PLATFORM_WIN_X86
		if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		{
			CPatch::RedirectFunction(0x732150, &CVisibilityPlugins__AtomicConstructor);
			CPatch::RedirectFunction(0x7321A0, &CVisibilityPlugins__AtomicDestructor);
		}
		#endif
	}

	// CVehicleModelInfo
	if (pFileIDlimits->bAreDifficultFileTypesInt32 || pOtherLimits->bIsVehicleColorIDextended)
	{
		#ifdef IS_PLATFORM_WIN_X86
		if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			CPatch::RedirectCode(0x4C75E9, &patch_CVehicleModelInfo__constructor_4C75E9);
		#endif
	}

	// CTimeModelInfo
	if (pFileIDlimits->bAreDifficultFileTypesInt32)
	{
		#ifdef IS_PLATFORM_WIN_X86
		if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			CPatch::RedirectCode(0x4C564E, &patch_CTimeModelInfo__constructor_4C564E);
		#endif
	}

	// CLodTimeModelInfo
	if (pFileIDlimits->bAreDifficultFileTypesInt32)
	{
		#ifdef IS_PLATFORM_WIN_X86
		if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			CPatch::RedirectCode(0x4C56A8, &patch_CLodTimeModelInfo__constructor_4C56A8);
		#endif
	}

	// CBaseModelInfo
	if (pFileIDlimits->bAreDifficultFileTypesInt32)
	{
		#ifdef IS_PLATFORM_WIN_X86
		if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		{
			CPatch::RedirectCode(0x4C4A68, &patch_CBaseModelInfo_constructor_4C4A68);	// CBaseModelInfo::CBaseModelInfo

			// Problem: CBaseModelInfo has a constructor inlined.
			CPatch::RedirectCode(0x4C4AF8, &patch_CBaseModelInfo__scalarDestructor_4C4AF8);	// CBaseModelInfo::~CBaseModelInfo(CBaseModelInfo this, bool bDelete)
			CPatch::RedirectCode(0x4C5590, Address_CBaseModelInfo_destructor);	// CAtomicModelInfo::~CAtomicModelInfo
			CPatch::RedirectCode(0x4C55D0, Address_CBaseModelInfo_destructor);	// CDamageAtomicModelInfo::~CDamageAtomicModelInfo
			CPatch::RedirectCode(0x4C5620, Address_CBaseModelInfo_destructor);	// CLodAtomicModelInfo::~CLodAtomicModelInfo

			CPatch::RedirectCode(0x4C56E0, Address_CBaseModelInfo_destructor);	// CLodTimeModelInfo::~CLodTimeModelInfo
			CPatch::RedirectCode(0x4C5750, Address_CBaseModelInfo_destructor);	// CClumpModelInfo::~CClumpModelInfo
			CPatch::RedirectCode(0x4C5790, Address_CBaseModelInfo_destructor);	// CWeaponModelInfo::~CWeaponModelInfo
			CPatch::RedirectCode(0x4C6333, &patch_CPedModelInfo__scalarDestructor_4C6333);	// CPedModelInfo::~CPedModelInfo(CPedModelInfo this, bool bDelete)

			CPatch::RedirectCode(0x4C5516, &patch_CBaseModelInfo__destructor_4C5516);	// CBaseModelInfo::~CBaseModelInfo
		}
		#endif
	}

	//  Multiple uses
	if (pFileIDlimits->bAreDifficultFileTypesInt32)
	{
		#ifdef IS_PLATFORM_WIN_X86
		if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		{
			CPatch::RedirectMethod(0x4C5680, &CBaseModelInfo_x12234<CTimeModelInfo__destructor_extraCode>::Destructor);
			CPatch::RedirectMethod(0x4C5590, &CBaseModelInfo_x12234<CLodTimeModelInfo__destructor_extraCode>::Destructor);
			CPatch::RedirectMethod(0x4C5920, &CBaseModelInfo_x12234<CVehicleModelInfo__destructor_extraCode>::Destructor);
		}
		#endif
	}

	// Furniture_c
	if (pFileIDlimits->bAreDifficultFileTypesInt32)
	{
		#ifdef IS_PLATFORM_WIN_X86
		if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		{
			CPatch::RedirectCode(0x590EC8, patch_Furniture_c__constructor_590EC8);
			CPatch::RedirectMethod(0x590ED0, &Furniture_c_535353::destructor);
		}
		#endif
	}

	// Model indices
	if (pFileIDlimits->bAreDifficultFileTypesInt32)
	{
		#ifdef IS_PLATFORM_WIN_X86
		if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		{
			static const uintptr_t pModelIndices[] =
			{
				0x8CD4F4,	// MI_TRAFFICLIGHTS
				0x8CD4F8,	// MI_TRAFFICLIGHTS_VERTICAL
				0x8CD4FC,	// MI_TRAFFICLIGHTS_MIAMI
				0x8CD500,	// MI_TRAFFICLIGHTS_VEGAS
				0x8CD504,	// MI_TRAFFICLIGHTS_TWOVERTICAL
				0x8CD508,	// MI_TRAFFICLIGHTS_3
				0x8CD50C,	// MI_TRAFFICLIGHTS_4
				0x8CD510,	// MI_TRAFFICLIGHTS_5
				0x8CD514,	// MI_TRAFFICLIGHTS_GAY
				0x8CD518,	// MI_SINGLESTREETLIGHTS1
				0x8CD51C,	// MI_SINGLESTREETLIGHTS2
				0x8CD520,	// MI_SINGLESTREETLIGHTS3
				0x8CD524,	// MI_DOUBLESTREETLIGHTS
				0x8CD528,	// MI_STREETLAMP1
				0x8CD52C,	// MI_STREETLAMP2
				0x8CD530,	// MODELID_CRANE_1
				0x8CD534,	// MODELID_CRANE_2
				0x8CD538,	// MODELID_CRANE_3
				0x8CD53C,	// MODELID_CRANE_4
				0x8CD540,	// MODELID_CRANE_5
				0x8CD544,	// MODELID_CRANE_6
				0x8CD548,	// MI_PARKINGMETER
				0x8CD54C,	// MI_PARKINGMETER2
				0x8CD550,	// MI_MALLFAN
				0x8CD554,	// MI_HOTELFAN_NIGHT
				0x8CD558,	// MI_HOTELFAN_DAY
				0x8CD55C,	// MI_HOTROOMFAN
				0x8CD560,	// MI_PHONEBOOTH1
				0x8CD564,	// MI_WASTEBIN
				0x8CD568,	// MI_BIN
				0x8CD56C,	// MI_POSTBOX1
				0x8CD570,	// MI_NEWSSTAND
				0x8CD574,	// MI_TRAFFICCONE
				0x8CD578,	// MI_DUMP1
				0x8CD57C,	// MI_ROADWORKBARRIER1
				0x8CD580,	// MI_ROADBLOCKFUCKEDCAR1
				0x8CD584,	// MI_ROADBLOCKFUCKEDCAR2
				0x8CD588,	// MI_BUSSIGN1
				0x8CD58C,	// MI_NOPARKINGSIGN1
				0x8CD590,	// MI_PHONESIGN
				0x8CD594,	// MI_FIRE_HYDRANT
				0x8CD598,	// MI_COLLECTABLE1
				0x8CD59C,	// MI_MONEY
				0x8CD5A0,	// MI_CARMINE
				0x8CD5A4,	// MI_NAUTICALMINE
				0x8CD5A8,	// MI_TELLY
				0x8CD5AC,	// MI_BRIEFCASE
				0x8CD5B0,	// MI_GLASS1
				0x8CD5B4,	// MI_GLASS8
				0x8CD5B8,	// MI_EXPLODINGBARREL
				0x8CD5BC,	// MI_PICKUP_ADRENALINE
				0x8CD5C0,	// MI_PICKUP_BODYARMOUR
				0x8CD5C4,	// MI_PICKUP_INFO
				0x8CD5C8,	// MI_PICKUP_HEALTH
				0x8CD5CC,	// MI_PICKUP_BONUS
				0x8CD5D0,	// MI_PICKUP_BRIBE
				0x8CD5D4,	// MI_PICKUP_KILLFRENZY
				0x8CD5D8,	// MI_PICKUP_CAMERA
				0x8CD5DC,	// MI_PICKUP_PARACHUTE
				0x8CD5E0,	// MI_PICKUP_REVENUE
				0x8CD5E4,	// MI_PICKUP_SAVEGAME
				0x8CD5E8,	// MI_PICKUP_PROPERTY
				0x8CD5EC,	// MI_PICKUP_PROPERTY_FORSALE
				0x8CD5F0,	// MI_PICKUP_CLOTHES
				0x8CD5F4,	// MI_PICKUP_2P_KILLFRENZY
				0x8CD5F8,	// MI_PICKUP_2P_COOP
				0x8CD5FC,	// MI_BOLLARDLIGHT
				0x8CD600,	// MI_FENCE
				0x8CD604,	// MI_FENCE2
				0x8CD608,	// MI_BUOY
				0x8CD60C,	// MI_PARKTABLE
				0x8CD610,	// MI_LAMPPOST1
				0x8CD614,	// MI_MLAMPPOST
				0x8CD618,	// MI_BARRIER1
				0x8CD61C,	// MI_LITTLEHA_POLICE
				0x8CD620,	// MI_TELPOLE02
				0x8CD624,	// MI_TRAFFICLIGHT01
				0x8CD628,	// MI_PARKBENCH
				0x8CD62C,	// MI_LIGHTBEAM
				0x8CD630,	// MI_AIRPORTRADAR
				0x8CD634,	// MI_RCBOMB
				0x8CD638,	// MI_BEACHBALL
				0x8CD63C,	// MI_SANDCASTLE1
				0x8CD640,	// MI_SANDCASTLE2
				0x8CD644,	// MI_JELLYFISH
				0x8CD648,	// MI_JELLYFISH01
				0x8CD64C,	// MI_FISH1SINGLE
				0x8CD650,	// MI_FISH1S
				0x8CD654,	// MI_FISH2SINGLE
				0x8CD658,	// MI_FISH2S
				0x8CD65C,	// MI_FISH3SINGLE
				0x8CD660,	// MI_FISH3S
				0x8CD664,	// MI_TURTLE
				0x8CD668,	// MI_DOLPHIN
				0x8CD66C,	// MI_SHARK
				0x8CD670,	// MI_SUBMARINE
				0x8CD674,	// MI_ESCALATORSTEP
				0x8CD678,	// MI_ESCALATORSTEP8
				0x8CD67C,	// MI_LOUNGE_WOOD_UP
				0x8CD680,	// MI_LOUNGE_TOWEL_UP
				0x8CD684,	// MI_LOUNGE_WOOD_DN
				0x8CD688,	// MI_LOTION
				0x8CD68C,	// MI_BEACHTOWEL01
				0x8CD690,	// MI_BEACHTOWEL02
				0x8CD694,	// MI_BEACHTOWEL03
				0x8CD698,	// MI_BEACHTOWEL04
				0x8CD69C,	// MI_BLIMP_NIGHT
				0x8CD6A0,	// MI_BLIMP_DAY
				0x8CD6A4,	// MI_YT_MAIN_BODY
				0x8CD6A8,	// MI_YT_MAIN_BODY2
				0x8CD6AC,	// MI_SAMSITE
				0x8CD6B0,	// MI_SAMSITE2
				0x8CD6B4,	// MI_TRAINCROSSING
				0x8CD6B8,	// MI_TRAINCROSSING1
				0x8CD6BC,	// MI_MAGNOCRANE
				0x8CD6C0,	// MI_CRANETROLLEY
				0x8CD6C4,	// MI_QUARRYCRANE_ARM
				0x8CD6C8,	// MI_OBJECTFORMAGNOCRANE1
				0x8CD6CC,	// MI_OBJECTFORMAGNOCRANE2
				0x8CD6D0,	// MI_OBJECTFORMAGNOCRANE3
				0x8CD6D4,	// MI_OBJECTFORMAGNOCRANE4
				0x8CD6D8,	// MI_OBJECTFORMAGNOCRANE5
				0x8CD6DC,	// MI_OBJECTFORBUILDINGSITECRANE1
				0x8CD6E0,	// MI_MAGNOCRANE_HOOK
				0x8CD6E4,	// MI_HARVESTERBODYPART1
				0x8CD6E8,	// MI_HARVESTERBODYPART2
				0x8CD6EC,	// MI_HARVESTERBODYPART3
				0x8CD6F0,	// MI_HARVESTERBODYPART4
				0x8CD6F4,	// MI_GRASSHOUSE
				0x8CD6F8,	// MI_GRASSPLANT
				0x8CD6FC,	// MI_CRANE_HARNESS
				0x8CD700,	// MI_CRANE_MAGNET
				0x8CD704,	// MI_QUARY_ROCK1
				0x8CD708,	// MI_QUARY_ROCK2
				0x8CD70C,	// MI_QUARY_ROCK3
				0x8CD710,	// MI_ATM
				0x8CD714,	// MI_DEAD_TIED_COP
				0x8CD718,	// MI_WINDSOCK
				0x8CD71C,	// MI_WRECKING_BALL
				0x8CD720,	// MI_FREEFALL_BOMB
				0x8CD724,	// MI_WONG_DISH
				0x8CD728,	// MI_GANG_DRINK
				0x8CD72C,	// MI_GANG_SMOKE
				0x8CD730,	// MI_RHYMESBOOK
				0x8CD734,	// MI_KMB_ROCK
				0x8CD738,	// MI_KMB_PLANK
				0x8CD73C,	// MI_KMB_BOMB
				0x8CD740,	// MI_MINI_MAGNET
				0x8CD744,	// MI_HANGING_CARCASS
				0x8CD748,	// MI_IMY_SHASH_WALL
				0x8CD74C,	// MI_PARACHUTE_BACKPACK
				0x8CD750,	// MI_OYSTER
				0x8CD754,	// MI_HORSESHOE
				0x8CD758,	// MI_OFFROAD_WHEEL
				0x8CD75C,	// MI_FLARE
				0x8CD760,	// MI_NITRO_BOTTLE_SMALL
				0x8CD764,	// MI_NITRO_BOTTLE_LARGE
				0x8CD768,	// MI_NITRO_BOTTLE_DOUBLE
				0x8CD76C,	// MI_HYDRAULICS
				0x8CD770,	// MI_STEREO_UPGRADE
				0x8CD774,	// MI_BASKETBALL
				0x8CD778,	// MI_POOL_CUE_BALL
				0x8CD77C,	// MI_PUNCHBAG
				0x8CD780,	// MI_IMY_GRAY_CRATE
			};

			for (uintptr_t address : pModelIndices)
				New_ID_from16bit((const void*)address);
		}
		#endif
	}

	// Vehicle colour variables
	if (g_otherLimits.bIsVehicleColorIDextended)
	{
		#ifdef IS_PLATFORM_WIN_X86
		if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		{
			New_ID_from8bit((uint8_t*)0xB4E3F0);	// PrimaryColor
			New_ID_from8bit((uint8_t*)0xB4E3F1);	// SecondaryColor
			New_ID_from8bit((uint8_t*)0xB4E3F2);	// TertiaryColor
			New_ID_from8bit((uint8_t*)0xB4E3F3);	// QuaternaryColor
		}
		#endif
	}	
}