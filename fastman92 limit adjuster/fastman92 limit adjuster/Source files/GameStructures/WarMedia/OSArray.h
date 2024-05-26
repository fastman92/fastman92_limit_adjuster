#pragma once

template <typename T> struct OSArray
{
	unsigned int numAlloced;
	unsigned int numEntries;
	T *dataPtr;
};