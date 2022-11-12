/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include <Assertions.h>
#include <stdint.h>

#include <DynamicTypes/DynamicStructure.h>

#if 0
struct tPoolObjectFlags
{
	char seed : 7;			// used to validate SCM handles
	char bIsFreeSlot : 1;
};

template<class A, class B = A> class CPool
{
public:
	B* m_Objects;
	tPoolObjectFlags* m_ByteMap;
	int32_t m_Size;		// max number of objects.
	int32_t m_Top;		// count of objects - 1
	bool m_bInitialized;
	char m_Field_11;

	// Initializes pool
	CPool* const Initialise(int maxCount, const char* poolName)
	{
		this -> m_Objects = new B[maxCount];

		this -> m_ByteMap = new tPoolObjectFlags[maxCount];

		this -> m_bInitialized = true;

		this -> m_Size = maxCount;

		this -> m_Top = -1;

		for (int i = 0; i < maxCount; i++)
		{
			this->m_ByteMap[i].seed = 0;
			this->m_ByteMap[i].bIsFreeSlot = true;
		}

		return this;
	}

	// Shutdown pool
	void Shutdown()
	{
		if(this -> m_bInitialized)
		{
			delete this -> m_Objects;
			delete this -> m_ByteMap;
		}

		this -> m_Objects = NULL;
		this -> m_ByteMap = NULL;
		this -> m_Size = 0;
		this -> m_Top = 0;
		this -> m_bInitialized = false;
	}

	// Clears pool
	void Clear()
	{
		if(!this -> m_bInitialized)
			return;

		for(int i = 0; i < this -> m_Size; i++)
			this -> m_ByteMap[i].bIsFreeSlot = true;
	}

	// Returns pointer to object by index
	A* AtIndex(int idx)
	{
		if(!this -> m_ByteMap[idx].bIsFreeSlot)
			return &this -> m_Objects[idx];
		else
			return nullptr;
	}

	// Returns if specified slot is free (0x404940)
	bool IsFreeSlotAtIndex(int idx)
	{
		return this -> m_ByteMap[idx].bIsFreeSlot != 0;
	}

	// Marks slot as free / used (0x404970)
	void SetStateAtIndex(int idx, char bIsSlotFree)
	{
		this -> m_ByteMap[idx].bIsFreeSlot = bIsSlotFree;
	}

	// Returns seed of object pointed by index (0x59F5F0)
	char GetSeedAtIndex(int idx)
	{
		return this -> m_ByteMap[idx].seed;
	}

	// Allocates object
	A* Allocate()
	{
		int startSearchFrom = this -> m_Top + 1;
		int searchTo = this -> m_Size;
		bool bSearchingFromBeginningDone = false;

		this -> m_Top++;

		while(true)
		{
			while(true)
			{
				if(this -> m_Top == searchTo)
					break;

				tPoolObjectFlags* objectFlags = &this -> m_ByteMap[this -> m_Top];

				if(objectFlags -> bIsFreeSlot)
				{
					objectFlags -> bIsFreeSlot = false;
					objectFlags -> seed = objectFlags -> seed ^ (objectFlags -> seed + 1);
					return &this -> m_Objects[this -> m_Top];
				}

				this -> m_Top++;
			}

			this -> m_Top = 0;

			if(!bSearchingFromBeginningDone)
			{
				searchTo = startSearchFrom;
				bSearchingFromBeginningDone = true;
			}
			else
				return NULL;
		}
	}

	// Deallocates object
	void Deallocate(A* pObject)
	{
		int idx = pObject - this -> m_Objects;

		this -> m_ByteMap[idx].bIsFreeSlot = true;
	}

	// Returns SCM handle for object
	int GetHandleByPointer(A* pObject)
	{
		int idx = pObject - this -> m_Objects;

		return idx * 256 + this -> m_ByteMap[idx].seed;
	}

	// Returns index by pointer
	int GetIndexByPointer(A* pObject)
	{
		return pObject - this->m_Objects;
	}

	// Returns pointer to object by SCM handle
	A* AtHandle(int handle)
	{
		int idx = handle / 256;

		return idx < this -> m_Size
			&& *(uint8_t*)&this -> m_ByteMap[idx] == *(uint8_t*)&handle ? &this -> m_Objects[idx] : NULL;
	}
};

typedef CPool<void> CPool_void;
VALIDATE_SIZE_ONLY_ON_32_BIT_ARCHITECTURE(CPool_void, 0x14);
#endif

/*
Plugin-SDK (Grand Theft Auto San Andreas) header file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/


/*
R* terminology      Our terminology
JustIndex           Index
Index               Id
Ref                 Handle/Ref
*/

union tPoolObjectFlags {
	struct {
		unsigned char nId : 7;
		bool bEmpty : 1;
	};
private:
	unsigned char nValue;
public:
	unsigned char IntValue() { return nValue; }
};

VALIDATE_SIZE(tPoolObjectFlags, 1);

template<class A, class B = A> class CPool_GTASA {
public:
	B                *m_pObjects;
	tPoolObjectFlags *m_byteMap;
	int               m_nSize;
	int               m_nFirstFree;
	bool              m_bOwnsAllocations;
	bool field_11;

	// Default constructor for statically allocated pools
	CPool_GTASA() {
		// Remember to call CPool::Init to fill in the fields!
		m_pObjects = nullptr;
		m_byteMap = nullptr;
		m_nSize = 0;
		m_bOwnsAllocations = false;
	}

	// Initializes pool
	CPool_GTASA(int nSize, const char* pPoolName) {
		m_pObjects = static_cast<B*>(operator new(TypeDetails::SizeOf<B>() * nSize));
		m_byteMap = static_cast<tPoolObjectFlags*>(operator new(sizeof(tPoolObjectFlags) * nSize));
		m_nSize = nSize;
		m_nFirstFree = -1;
		m_bOwnsAllocations = true;
		for (int i = 0; i < nSize; ++i) {
			m_byteMap[i].bEmpty = true;
			m_byteMap[i].nId = 0;
		}
	}

	~CPool_GTASA() {
		Flush();
	}

	// Initialises a pool with preallocated
	// To be called one-time-only for statically allocated pools.
	void Init(int nSize, void* pObjects, void* pInfos) {
		// Since we statically allocated the pools we do not deallocate.
		assert(this->m_pObjects == nullptr);
		m_pObjects = static_cast<B*>(pObjects);
		m_byteMap = static_cast<tPoolObjectFlags*>(pInfos);
		m_nSize = nSize;
		m_nFirstFree = -1;
		m_bOwnsAllocations = false;
		for (int i = 0; i < nSize; ++i) {
			m_byteMap[i].bEmpty = true;
			m_byteMap[i].nId = 0;
		}
	}

	// Shutdown pool
	void Flush() {
		if (m_bOwnsAllocations) {
			operator delete(m_pObjects);
			operator delete(m_byteMap);
		}
		m_pObjects = nullptr;
		m_byteMap = nullptr;
		m_nSize = 0;
		m_nFirstFree = 0;
	}

	// Clears pool
	void Clear() {
		for (int i = 0; i < m_nSize; i++)
			m_byteMap[i].bEmpty = true;
	}

	// Returns if specified slot is free (0x404940)
	bool IsFreeSlotAtIndex(int idx) {
		return m_byteMap[idx].bEmpty;
	}

	// Returns slot index for this object
	int GetIndex(A* pObject) {
		return reinterpret_cast<B*>(pObject) - m_pObjects;
	}

	// Returns pointer to object by slot index
	A* GetAt(int nIndex) {
		return !IsFreeSlotAtIndex(nIndex) ? (A *)&m_pObjects[nIndex] : nullptr;
	}

	// Marks slot as free / used (0x404970)
	void SetFreeAt(int idx, bool bFree) {
		m_byteMap[idx].bEmpty = bFree;
	}

	// Set new id for slot (0x54F9F0)
	void SetIdAt(int idx, unsigned char id) {
		m_byteMap[idx].nId = id;
	}

	// Get id for slot (0x552200)
	unsigned char GetIdAt(int idx) {
		return m_byteMap[idx].nId;
	}

	// Allocates object
	A* New() {
		bool bReachedTop = false;
		do {
			if (++m_nFirstFree >= m_nSize) {
				if (bReachedTop) {
					m_nFirstFree = -1;
					return nullptr;
				}
				bReachedTop = true;
				m_nFirstFree = 0;
			}
		} while (!m_byteMap[m_nFirstFree].bEmpty);
		m_byteMap[m_nFirstFree].bEmpty = false;
		++m_byteMap[m_nFirstFree].nId;
		return &m_pObjects[m_nFirstFree];
	}

	// Allocates object at a specific index from a SCM handle (ref) (0x59F610)
	void CreateAtRef(int nRef) {
		nRef >>= 8;
		m_byteMap[nRef].bEmpty = false;
		++m_byteMap[nRef].nId;
		m_nFirstFree = 0;
		while (!m_byteMap[m_nFirstFree].bEmpty)
			++m_nFirstFree;
	}

	// (0x5A1C00)
	A *New(int nRef) {
		A *result = &m_pObjects[nRef >> 8];
		CreateAtRef(nRef);
		return result;
	}

	// Deallocates object
	void Delete(A* pObject) {
		int nIndex = reinterpret_cast<B*>(pObject) - m_pObjects;
		m_byteMap[nIndex].bEmpty = true;
		if (nIndex < m_nFirstFree)
			m_nFirstFree = nIndex;
	}

	// Returns SCM handle (ref) for object (0x424160)
	int GetRef(A* pObject) {
		return (GetIndex(pObject) << 8) + m_byteMap[GetIndex(pObject)].IntValue();
	}

	// Returns pointer to object by SCM handle (ref)
	A* GetAtRef(int ref) {
		int nSlotIndex = ref >> 8;
		return nSlotIndex >= 0 && nSlotIndex < m_nSize && m_byteMap[nSlotIndex].IntValue() == (ref & 0xFF) ? reinterpret_cast<A*>(&m_pObjects[nSlotIndex]) : nullptr;
	}

	// (0x54F6B0)
	unsigned int GetNoOfUsedSpaces() {
		unsigned int counter = 0;
		for (int i = 0; i < m_nSize; ++i) {
			if (!IsFreeSlotAtIndex(i))
				++counter;
		}
		return counter;
	}

	unsigned int GetNoOfFreeSpaces() {
		return m_nSize - GetNoOfUsedSpaces();
	}

	// (0x54F690)
	unsigned int GetObjectSize() {
		return TypeDetails::SizeOf<B>();
	}

	// (0x5A1CD0)
	bool IsObjectValid(A *obj) {
		int slot = GetIndex(obj);
		return slot >= 0 && slot < m_nSize && !IsFreeSlotAtIndex(slot);
	}
};

typedef CPool_GTASA<void> CPool_GTASA_void;
VALIDATE_SIZE_ONLY_ON_32_BIT_ARCHITECTURE(CPool_GTASA_void, 0x14);

// GTA IV
template<class A, class B = A> class CPool_GTAIV	// to do
{
	B* m_Objects;
	tPoolObjectFlags* m_ByteMap;
	int32_t m_Size;
	unsigned int m_sizeOfOneElement;
	int32_t m_Top;
	int field_14;
	bool m_bInitialized;
};