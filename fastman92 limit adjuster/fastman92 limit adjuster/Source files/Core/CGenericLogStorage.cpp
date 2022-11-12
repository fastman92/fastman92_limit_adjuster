/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CGenericLogStorage.h"
#include <string.h>
#include <stdio.h>
#include "FormattedOutput.h"

#ifdef IS_PLATFORM_WIN
#include <Windows.h>
#endif

// File handle
FILE* CGenericLogStorage::ms_FileHandle = NULL;

// Work buffer
char* CGenericLogStorage::ms_WorkBuffer = NULL;

// Work buffer size
unsigned int CGenericLogStorage::ms_WorkBufferSize = 0;

// Work buffer pos
unsigned int CGenericLogStorage::ms_WorkBufferPos = 0;

// One time initialization done
bool CGenericLogStorage::ms_oneTimeInitalizationDone = false;

// Write a new line
void CGenericLogStorage::WriteNewLine()
{
	CGenericLogStorage::SaveDataToWorkBuffer("\n", 1);
}

// Write a line separation
void CGenericLogStorage::WriteLineSeparator()
{
	CGenericLogStorage::SaveText("\n---------------------------------------------");
}

#ifdef IS_PLATFORM_WIN
static CRITICAL_SECTION criticalSection;
#endif

void CGenericLogStorage::EnterCriticalSection()
{
	#ifdef IS_PLATFORM_WIN
	::EnterCriticalSection(&criticalSection);
	#endif
}

void CGenericLogStorage::LeaveCriticalSection()
{
	#ifdef IS_PLATFORM_WIN
	::LeaveCriticalSection(&criticalSection);
	#endif
}

// Initializes writing
void CGenericLogStorage::Initialise()
{
	if(!ms_oneTimeInitalizationDone)
	{
		#ifdef IS_PLATFORM_WIN
			InitializeCriticalSection(&criticalSection);
		#endif

		ms_oneTimeInitalizationDone = true;
	}

	if (!ms_WorkBuffer)
	{
		CGenericLogStorage::ms_WorkBufferSize = 4096;
		CGenericLogStorage::ms_WorkBuffer = new char[CGenericLogStorage::ms_WorkBufferSize];

		CGenericLogStorage::ms_WorkBufferPos = 0;
	}
}

// Opens file for text writing
void CGenericLogStorage::OpenFileForTextWriting(const char* filename)
{
	if (CGenericLogStorage::IsFileOpen())
		CGenericLogStorage::CloseFile();

	CGenericLogStorage::Initialise();

	CGenericLogStorage::ms_FileHandle = fopen(filename, "w");

	CGenericLogStorage::SaveWorkBuffer();
}

// Returns true if file is open
bool CGenericLogStorage::IsFileOpen()
{
	return CGenericLogStorage::ms_FileHandle != NULL;
}

// Saves text
void CGenericLogStorage::SaveText(const char * text)
{
	CGenericLogStorage::SaveDataToWorkBuffer(text, strlen(text));
}

// Saves new line + text
void CGenericLogStorage::SaveTextLn(const char * text)
{
	CGenericLogStorage::WriteNewLine();

	CGenericLogStorage::SaveDataToWorkBuffer(text, strlen(text));
}

// Saves formatted text
void CGenericLogStorage::SaveFormattedTextVArgs(const char * format, va_list list)
{
	char buffer[4096];

#ifdef IS_PLATFORM_WIN
	int l = _vsnprintf_s(buffer, _countof(buffer), _TRUNCATE, format, list);

	CGenericLogStorage::SaveDataToWorkBuffer(buffer, l);
#elif defined(IS_PLATFORM_ANDROID)
	int l = vsnprintf(buffer, sizeof(buffer), format, list);
	CGenericLogStorage::SaveDataToWorkBuffer(buffer, l);
#endif
}

// Saves formatted text
void CGenericLogStorage::SaveFormattedText(const char * format, ...)
{
	va_list vl;
	va_start(vl, format);
	CGenericLogStorage::SaveFormattedTextVArgs(format, vl);
	va_end(vl);
}

// Saves new line + formatted text
void CGenericLogStorage::SaveFormattedTextLn(const char * format, ...)
{
	va_list vl;
	va_start(vl, format);
	CGenericLogStorage::WriteNewLine();
	CGenericLogStorage::SaveFormattedTextVArgs(format, vl);
	va_end(vl);
}

// Saves data to work buffer
bool CGenericLogStorage::SaveDataToWorkBuffer(const void *ptr, size_t size)
{
	if (size == 0)
		return true;

	CGenericLogStorage::EnterCriticalSection();

	if(ms_FileHandle)
	{
		while(true)
		{
			if(CGenericLogStorage::ms_WorkBufferPos + size > CGenericLogStorage::ms_WorkBufferSize)
			{
				size_t allowedSize = CGenericLogStorage::ms_WorkBufferSize - CGenericLogStorage::ms_WorkBufferPos;

				memcpy(CGenericLogStorage::ms_WorkBuffer + CGenericLogStorage::ms_WorkBufferPos, ptr, allowedSize);

				fwrite(CGenericLogStorage::ms_WorkBuffer, CGenericLogStorage::ms_WorkBufferSize, 1, CGenericLogStorage::ms_FileHandle);

				CGenericLogStorage::ms_WorkBufferPos = 0;
				size -= allowedSize;

				ptr = (const char*)ptr + allowedSize;
			}
			else
			{
				memcpy(CGenericLogStorage::ms_WorkBuffer + CGenericLogStorage::ms_WorkBufferPos, ptr, size);
				CGenericLogStorage::ms_WorkBufferPos += size;
				break;
			}
		}
	}
	else if(CGenericLogStorage::ms_WorkBuffer)	// write until whole buffer is full
	{
		size_t allowedSize = size;

		if (CGenericLogStorage::ms_WorkBufferPos + size > CGenericLogStorage::ms_WorkBufferSize)
			allowedSize = CGenericLogStorage::ms_WorkBufferSize - CGenericLogStorage::ms_WorkBufferPos;

		if (allowedSize)
		{
			memcpy(CGenericLogStorage::ms_WorkBuffer + CGenericLogStorage::ms_WorkBufferPos, ptr, allowedSize);
			CGenericLogStorage::ms_WorkBufferPos += allowedSize;
		}
	}

	CGenericLogStorage::LeaveCriticalSection();

	return true;
}

// Saves work buffer
void CGenericLogStorage::SaveWorkBuffer()
{
	if (!CGenericLogStorage::ms_FileHandle)
		return;

	if (CGenericLogStorage::ms_WorkBufferPos == 0)
		return;

	CGenericLogStorage::EnterCriticalSection();

	fwrite(CGenericLogStorage::ms_WorkBuffer, CGenericLogStorage::ms_WorkBufferPos, 1, CGenericLogStorage::ms_FileHandle);

	CGenericLogStorage::ms_WorkBufferPos = 0;

	fflush(CGenericLogStorage::ms_FileHandle);

	CGenericLogStorage::LeaveCriticalSection();
}

// Closes file
void CGenericLogStorage::CloseFile()
{
	if (ms_FileHandle)
	{
		CGenericLogStorage::SaveWorkBuffer();

		fclose(CGenericLogStorage::ms_FileHandle);
	}

	delete[] CGenericLogStorage::ms_WorkBuffer;
	CGenericLogStorage::ms_FileHandle = NULL;
	CGenericLogStorage::ms_WorkBufferPos = 0;
	CGenericLogStorage::ms_WorkBufferSize = 0;
}