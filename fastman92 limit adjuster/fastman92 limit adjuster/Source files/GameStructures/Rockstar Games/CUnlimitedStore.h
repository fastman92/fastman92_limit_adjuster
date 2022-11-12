/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include <vector>

template<typename T> class CUnlimitedStore
{
	std::vector<T*> m_Entries;

public:
	// Allocates item
	T* AllocateItem()
	{
		T* ptr = new T();
		this->m_Entries.push_back(ptr);
		return ptr;
	}

	// Clears
	void Clear()
	{
		typename std::vector<T*>::iterator it;

		for (it = this->m_Entries.begin(); it != this->m_Entries.end(); it++)
			delete *it;
		this->m_Entries.clear();
	}

	// Destructor
	~CUnlimitedStore()
	{
		this->Clear();
	}
};