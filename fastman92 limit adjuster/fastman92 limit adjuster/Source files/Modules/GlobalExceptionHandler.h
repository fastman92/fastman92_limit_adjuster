/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "../Core/CLimitAdjusterModule.h"

#ifdef IS_PLATFORM_WIN
#include <Windows.h>
#endif

#ifdef IS_PLATFORM_ANDROID
#include <list>
#include <signal.h>
#endif

#include <string>
#include <stdint.h>

struct tSSEregister
{
	float a;
	float b;
	float c;
	float d;
};

struct tExceptionInfoPrinting
{
	// unsigned int msgBoxOffset;
	// char msgBoxStr[1024];
	std::string msgBoxStr;

	void Init() {
		this->msgBoxStr.clear();
		// this->msgBoxOffset = 0;
		// this->msgBoxStr[0] = 0;
	}
};

struct tExceptionInfo
{
	#ifdef IS_PLATFORM_WIN
	EXCEPTION_POINTERS* ep;
	#elif defined(IS_PLATFORM_ANDROID)
	int sig;
	siginfo_t *siginfo;
	ucontext_t *context;
	#endif
};

struct tMemoryRegionInformation
{
	void* start;
	void* end;
	char permissions[10];
	std::string pathname;
};

class GlobalExceptionHandler : public CLimitAdjusterModule
{
	#ifdef IS_PLATFORM_WIN 
	static CRITICAL_SECTION crashCriticalSection;
	#endif

public:
	static bool bIsExceptionHandlerRegistered;
	static bool bDisableMusicPlaying;

	static wchar_t DebugStr[4096];
	static int DebugStrOffset;

	#ifdef IS_PLATFORM_WIN 
	// Last file loaded
	static char ms_LastFileLoaded[1024];

	// Last library loaded
	static char ms_LastLibraryLoaded[1024];
	#endif

	// Print to variables
	static void PrintfToBuffer(tExceptionInfoPrinting* pPrinting, bool bPrintToFile, bool bPrintToMsgBox, const char* format, ...);

	// Prints the exception address
	static void PrintExceptionAddress(tExceptionInfoPrinting* pPrinting, uintptr_t exceptionAddress, const char* exceptionModuleAddressStr);

	// Prints an information about screenshot
	static void PrintInformationAboutScreenshot(tExceptionInfoPrinting* pPrinting);

	// Prints a stack dump
	static void PrintStackDump(tExceptionInfoPrinting* printing, tExceptionInfo* pExceptionInfo);

#ifdef IS_PLATFORM_WIN
	// Exception handler
	static LONG CALLBACK RunExceptionHandler(EXCEPTION_POINTERS* ep);	
#elif defined(IS_PLATFORM_ANDROID)
	// Exception handler
	static void RunExceptionHandler(int sig, siginfo_t *siginfo, void *context);
#endif

#ifdef IS_PLATFORM_WIN_X86
	// Debug exception handler
	static void DebugExceptionHandler();
#endif

	// Returns true if exception handler is registered
	static bool IsExceptionHandlerRegistered();

	// Set unhandled exception handler
	static void RegisterUnhandledExceptionHandler();

	// Disables music playing
	static void DisableMusicPlaying(bool bDisable);

	#if IS_PLATFORM_WIN
	// Returns exception name by code
	static const char* GetExceptionName(uint32_t exceptionCode);
	#elif defined(IS_PLATFORM_ANDROID) || defined(IS_PLATFORM_LINUX)
	// Returns exception name by code
	static void GetExceptionName(int sig, int exceptionCode, const char** ppSignalName, const char** ppCodeName);
	#endif

	#ifdef IS_PLATFORM_WIN_X86
	// Read long double
	static long double __cdecl ReadLongDouble(void* ptr);
	#endif

	// Initialize
	virtual void Initialise() {}

	// Shutdown
	virtual void Shutdown() {}
};

extern GlobalExceptionHandler g_GlobalExceptionHandler;