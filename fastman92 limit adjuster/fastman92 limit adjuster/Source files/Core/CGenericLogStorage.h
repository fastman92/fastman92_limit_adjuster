/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include <stdarg.h>
#include <stdio.h>

class CGenericLogStorage
{
private:
	// File handle
	static FILE* ms_FileHandle;

	// Work buffer
	static char* ms_WorkBuffer;
	
	// Work buffer size
	static unsigned int ms_WorkBufferSize;

	// Work buffer pos
	static unsigned int ms_WorkBufferPos;

	// One time initialization done
	static bool ms_oneTimeInitalizationDone;

	static void EnterCriticalSection();
	static void LeaveCriticalSection();

public:
	// Initializes writing
	static void Initialise();

	// Opens file for text writing
	static void OpenFileForTextWriting(const char* filename);

	// Returns true if file is open
	static bool IsFileOpen();

	// Write a new line
	static void WriteNewLine();

	// Write a line separation
	static void WriteLineSeparator();

	// Saves text
	static void SaveText(const char * text);

	// Saves new line + text
	static void SaveTextLn(const char * text);

private:
	// Saves formatted text
	static void SaveFormattedTextVArgs(const char * format, va_list list);

public:
	// Saves formatted text
	static void SaveFormattedText(const char * format, ...);

	// Saves new line + formatted text
	static void SaveFormattedTextLn(const char * format, ...);

	// Saves data to work buffer
	static bool SaveDataToWorkBuffer(const void *ptr, size_t size);
	
	// Saves work buffer
	static void SaveWorkBuffer();
	
	// Closes file
	static void CloseFile();
};