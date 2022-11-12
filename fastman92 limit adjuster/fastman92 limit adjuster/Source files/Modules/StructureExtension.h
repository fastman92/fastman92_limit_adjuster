/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "../Core\CLimitAdjusterModule.h"
#include "../GameStructures/Rockstar Games/CEntity.h"
#include <Android\preferedUnorderedMap.h>

#include "../GameStructures/Rockstar Games/CCollisionFile.h"
#include "../GameStructures/Rockstar Games/CColModel.h"
#include "../GameStructures/Rockstar Games/CEntity.h"
#include "../GameStructures/Rockstar Games/CIplFile.h"
#include "../GameStructures/Rockstar Games/CVehicle.h"

class CPed_generic;

#define MAKE_STRUCT_EXT_LIST(formatMacro) \
	formatMacro(CCollisionFile) \
	formatMacro(CColModel) \
	formatMacro(CEntity) \
	formatMacro(CIplFile) \
	formatMacro(CObject) \
	formatMacro(CVehicle)	

#define GET_STRUCT_EXT_MEMBER_NAME(type) m_##type##Extension
#define DECLARE_STRUCT_EXT_CONTAINER(type) CStructureExtensionContainer<type##_generic, type##_extension> GET_STRUCT_EXT_MEMBER_NAME(type);

#define DECLARE_GET_STRUCT_EXT_DATA(type) type##_extension* GetExtDataFor##type(const type##_generic* basicPtr);

MAKE_STRUCT_EXT_LIST(DECLARE_GET_STRUCT_EXT_DATA);

// extended ID
// Creates new ID
int32_t* New_ID_from16bit(const void* pBasicID);

// Removes the ID
void Delete_ID_from16bit(const void* pBasicID);

// debug functions
int32_t GetExtendedIDfrom16bitBeforeFilter(const void* basicPtr, uintptr_t locationChanged);
void SetExtendedIDfrom16bitBeforeFilter(void* basicPtr, int32_t ID, uintptr_t locationChanged);
void MarkExecuted(uintptr_t locationChanged);

template<class basic, class ext> class CStructureExtensionContainer
{
private:
	prefered_unordered_map<const basic*, ext> map;

	bool bIsEnabled;

public:
	// Constructor
	CStructureExtensionContainer()
	{
		this->bIsEnabled = false;
	}

	// Returns pointer to extended data
	ext* GetPointerToExtendedData(const basic* basicPtr)
	{
		auto it = map.find(basicPtr);
		
		if (it != map.end())
			return &it->second;
		else
			return nullptr;
	}

	ext* New(const basic* basicPtr)
	{
		ext obj;
		auto it = map.insert(std::pair<const basic*, ext>(basicPtr, obj));
		return &it.first->second;
	}

	void Delete(const basic* basicPtr)
	{
		map.erase(basicPtr);
	}

	// Enables the container
	void Enable()
	{
		this->bIsEnabled = true;
	}

	// Checks if enabled
	bool IsEnabled()
	{
		return this->bIsEnabled;
	}

	// Returns count of items
	unsigned int GetCount()
	{
		return this->map.size();
	}
};

#define MAKE_INTEGER_EXTENSION_LIST(formatMacro) \
	formatMacro(int32_t, ID_extensionFrom8bit) \
	formatMacro(int32_t, ID_extensionFrom16bit) \
	formatMacro(uint32_t, CLinkAddress_extension)

#define GET_INTEGER_EXTENSION_MEMBER_NAME(name) m_##name

#define DECLARE_GET_INTEGER_EXT_DATA(type, name) type* GetExtDataPtrFor##name(const void* basicPtr);

#define DECLARE_INTEGER_EXT_CONTAINER(type, name) CStructureExtensionContainer<void, type> GET_INTEGER_EXTENSION_MEMBER_NAME(name);

extern "C"
{
	MAKE_INTEGER_EXTENSION_LIST(DECLARE_GET_INTEGER_EXT_DATA);
}

class StructureExtension : public CLimitAdjusterModule
{
public:
	MAKE_STRUCT_EXT_LIST(DECLARE_STRUCT_EXT_CONTAINER);
	MAKE_INTEGER_EXTENSION_LIST(DECLARE_INTEGER_EXT_CONTAINER);

	// Initialize
	virtual void Initialise() {}

	// Shutdown
	virtual void Shutdown() {}

	// Processes
	void ApplyHook();
};

extern StructureExtension g_structureExtension;