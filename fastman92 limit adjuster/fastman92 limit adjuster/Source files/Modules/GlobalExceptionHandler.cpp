/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "GlobalExceptionHandler.h"
#include <fileIO.h>

#include "../Core/CPatch.h"
#include "../Core/CGenericLogStorage.h"
#include "../Core/FormattedOutput.h"
#include "../Core/LimitAdjuster.h"

#include <Array/countof.h>
#include <MultiPlatformSupport/PlatformGeneralisation.h>

#ifdef IS_PLATFORM_WIN
#include "../resources/resource.h"

#include <float.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include <NtDsAPI.h>
#include <Windows.h>

	#if defined(IS_ARCHITECTURE_X86) || defined(IS_ARCHITECTURE_X64)
	#include <MinHook\include\MinHook.h>
	#endif
#endif

#ifdef IS_PLATFORM_ANDROID
#include <StrLexStuff.h>

#include <list>
#include <unistd.h>
#endif

using namespace Game;

GlobalExceptionHandler g_GlobalExceptionHandler;

#ifdef IS_PLATFORM_WIN
CRITICAL_SECTION GlobalExceptionHandler::crashCriticalSection;
#endif

bool GlobalExceptionHandler::bIsExceptionHandlerRegistered = false;
bool GlobalExceptionHandler::bDisableMusicPlaying = false;
wchar_t GlobalExceptionHandler::DebugStr[4096] = L"";
int GlobalExceptionHandler::DebugStrOffset = 0;

#ifdef IS_PLATFORM_ANDROID
const unsigned int installedSignalArray[] = { SIGSEGV, SIGFPE, SIGINT, SIGILL, SIGBUS };
struct sigaction oldSignalActionArray[_countof(installedSignalArray)];

struct sigaction* GetPointerToOldSigAction(unsigned int sigID)
{
	for (int i = 0; i < _countof(installedSignalArray); i++)
		if (installedSignalArray[i] == sigID)
			return oldSignalActionArray + i;

	return NULL;
}

#endif

#ifdef IS_PLATFORM_WIN
// Last file loaded
char GlobalExceptionHandler::ms_LastFileLoaded[1024] = "";

// Last library loaded
char GlobalExceptionHandler::ms_LastLibraryLoaded[1024] = "";


static HANDLE (WINAPI *RealCreateFileA)(
    __in     LPCSTR lpFileName,
    __in     DWORD dwDesiredAccess,
    __in     DWORD dwShareMode,
    __in_opt LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    __in     DWORD dwCreationDisposition,
    __in     DWORD dwFlagsAndAttributes,
    __in_opt HANDLE hTemplateFile
	)	
	= CreateFileA;

// Detoured CreateFileA
HANDLE WINAPI DetouredCreateFileA(
    __in     LPCSTR lpFileName,
    __in     DWORD dwDesiredAccess,
    __in     DWORD dwShareMode,
    __in_opt LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    __in     DWORD dwCreationDisposition,
    __in     DWORD dwFlagsAndAttributes,
    __in_opt HANDLE hTemplateFile
								 )
{
	/*
	CGenericLogStorage::SaveFormattedTextLn("File loaded %s", lpFileName);
	CGenericLogStorage::SaveWorkBuffer();
	*/

	strncpy(GlobalExceptionHandler::ms_LastFileLoaded,
		lpFileName,
		sizeof(GlobalExceptionHandler::ms_LastFileLoaded));

	return RealCreateFileA(lpFileName,
		dwDesiredAccess,dwShareMode,
		lpSecurityAttributes,dwCreationDisposition,
		dwFlagsAndAttributes,
		hTemplateFile);
}

// Detoured CreateFileW
static HANDLE
(WINAPI*
	RealCreateFileW)(
		_In_ LPCWSTR lpFileName,
		_In_ DWORD dwDesiredAccess,
		_In_ DWORD dwShareMode,
		_In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes,
		_In_ DWORD dwCreationDisposition,
		_In_ DWORD dwFlagsAndAttributes,
		_In_opt_ HANDLE hTemplateFile
		) = &CreateFileW;

HANDLE
WINAPI
DetouredCreateFileW(
	_In_ LPCWSTR lpFileName,
	_In_ DWORD dwDesiredAccess,
	_In_ DWORD dwShareMode,
	_In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	_In_ DWORD dwCreationDisposition,
	_In_ DWORD dwFlagsAndAttributes,
	_In_opt_ HANDLE hTemplateFile
)
{
	/*
	if (!wcscmp(lpFileName, L"D:\\Games\\GTASADE\\Gameface\\Content\\SanAndreas\\Vehicles\\SKR_greenwoo.uasset"))
	{
		printf_MessageBox("Stop");
	}

	CGenericLogStorage::SaveFormattedTextLn("File loadedw %ls", lpFileName);
	CGenericLogStorage::SaveWorkBuffer();
	*/

	return RealCreateFileW(lpFileName,
		dwDesiredAccess, dwShareMode,
		lpSecurityAttributes, dwCreationDisposition,
		dwFlagsAndAttributes,
		hTemplateFile);
}

static HMODULE (WINAPI *RealLoadLibrary)(__in LPCSTR lpLibFileName) = LoadLibraryA;

__out_opt
HMODULE
WINAPI
DetouredLoadLibraryA(
    __in LPCSTR lpLibFileName
    )
{
	strncpy(GlobalExceptionHandler::ms_LastLibraryLoaded,
		lpLibFileName,
		sizeof(GlobalExceptionHandler::ms_LastLibraryLoaded)
		);

	////////////

	HMODULE hModule;		
	
	hModule = RealLoadLibrary(lpLibFileName);

	return hModule;
}

static __out_opt
HMODULE
(WINAPI*
RealKernelBase_LoadLibraryExW)(
    __in       LPCWSTR lpLibFileName,
    __reserved HANDLE hFile,
    __in       DWORD dwFlags
	);

static LPTOP_LEVEL_EXCEPTION_FILTER
(WINAPI* RealSetUnhandledExceptionFilter)(
	__in_opt LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter
) = SetUnhandledExceptionFilter;

// For debugging
/*
static void ShowReturnAddress(uintptr_t address, uintptr_t esp)
{
	printf_MessageBox("Return address: 0x%p esp: 0x%p", address, esp);
}

NAKED LPTOP_LEVEL_EXCEPTION_FILTER
WINAPI
DetouredSetUnhandledExceptionFilterDebug(
	__in_opt LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter
)
{
	__asm
	{
		mov rcx, [rsp];
		mov rdx, rsp;
		jmp ShowReturnAddress;
	}

	// return RealSetUnhandledExceptionFilter(lpTopLevelExceptionFilter);
}
*/

LPTOP_LEVEL_EXCEPTION_FILTER
WINAPI
DetouredSetUnhandledExceptionFilter(
	__in_opt LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter
)
{
	return 0;

	// return RealSetUnhandledExceptionFilter(lpTopLevelExceptionFilter);
}

int
(WINAPI*
	RealMessageBoxA)(
		_In_opt_ HWND hWnd,
		_In_opt_ LPCSTR lpText,
		_In_opt_ LPCSTR lpCaption,
		_In_ UINT uType) = MessageBoxA;

int
WINAPI
DetouredMessageBoxA(
	_In_opt_ HWND hWnd,
	_In_opt_ LPCSTR lpText,
	_In_opt_ LPCSTR lpCaption,
	_In_ UINT uType)
{
	return RealMessageBoxA(hWnd, lpText, lpCaption, uType);
}
#endif

#ifdef IS_PLATFORM_WIN_X64
void* getNextAdressOfDllFunctionChecked()
{
	return &GetFileInformationByHandle;
}
#endif

#ifdef IS_PLATFORM_WIN_X86
// Debug exception handler
void GlobalExceptionHandler::DebugExceptionHandler()
{
    EXCEPTION_RECORD ExceptionRecord;
    CONTEXT ContextRecord;

	// set data
	{
		ExceptionRecord.ExceptionCode = EXCEPTION_ACCESS_VIOLATION;
	
		// General registers
		ContextRecord.Eax = 1;
		ContextRecord.Ebx = 2;
		ContextRecord.Ecx = 3;
		ContextRecord.Edx = 4;
		ContextRecord.Esi = 5;
		ContextRecord.Edi = 6;
		ContextRecord.Ebp = 7;
		ContextRecord.Esp = 8;
		ContextRecord.Eip = 9;
		ContextRecord.EFlags = 10;
		
		// FPU registers
		for(int i = 0; i < 8; i++)
		{
			ContextRecord.FloatSave.RegisterArea[i * 10 + 0] = 0;
			ContextRecord.FloatSave.RegisterArea[i * 10 + 1] = 0;
			ContextRecord.FloatSave.RegisterArea[i * 10 + 2] = 0;
			ContextRecord.FloatSave.RegisterArea[i * 10 + 3] = 0;
			ContextRecord.FloatSave.RegisterArea[i * 10 + 4] = 0;
			ContextRecord.FloatSave.RegisterArea[i * 10 + 5] = 0;
			ContextRecord.FloatSave.RegisterArea[i * 10 + 6] = 0;
			ContextRecord.FloatSave.RegisterArea[i * 10 + 7] = 0x80;
			ContextRecord.FloatSave.RegisterArea[i * 10 + 8] = 0xFC;
			ContextRecord.FloatSave.RegisterArea[i * 10 + 9] = 0x3F;
		}
	}

	// run it
	EXCEPTION_POINTERS ep;
	ep.ContextRecord = &ContextRecord;
	ep.ExceptionRecord = &ExceptionRecord;

	RunExceptionHandler(&ep);
}
#endif


#ifdef IS_PLATFORM_ANDROID
std::list<tMemoryRegionInformation> ListOfMemoryRegions;
#endif

static const float myFloat = (float)0.125;

static const tSSEregister sseFloat =
{
	myFloat,
	myFloat,
	myFloat,
	myFloat
};

#ifdef IS_PLATFORM_WIN_X86
NAKED void patch_test()
{
	__asm
	{
		
		fld dword ptr[myFloat];
		fld dword ptr[myFloat];
		fld dword ptr[myFloat];
		fld dword ptr[myFloat];
		fld dword ptr[myFloat];
		fld dword ptr[myFloat];
		fld dword ptr[myFloat];
		fld dword ptr[myFloat];

		xor eax, eax;
		xor ebx, ebx;
		xor ecx, ecx;
		xor edx, edx;
		xor edi, edi;
		xor esi, esi;
		xor ebp, ebp;
		xor esp, esp;
		
		movdqu xmm0, sseFloat;

		mov eax, 7;
		mov eax, [eax];
	}
}
#endif

// Returns true if exception handler is registered
bool GlobalExceptionHandler::IsExceptionHandlerRegistered()
{
	return GlobalExceptionHandler::bIsExceptionHandlerRegistered;
}

// Set unhandled exception handler
void GlobalExceptionHandler::RegisterUnhandledExceptionHandler()
{
	MAKE_VAR_GAME_VERSION();

	// Initialisation of variables
	#if IS_PLATFORM_WIN
	GlobalExceptionHandler::ms_LastLibraryLoaded[0] = 0;
	GlobalExceptionHandler::ms_LastFileLoaded[0] = 0;
	#endif

	// Registration of exception handler
	#if IS_PLATFORM_WIN
	InitializeCriticalSection(&GlobalExceptionHandler::crashCriticalSection);
	
	SetUnhandledExceptionFilter(&GlobalExceptionHandler::RunExceptionHandler);
	
	// GlobalExceptionHandler::DebugExceptionHandler();
	
	#elif defined(IS_PLATFORM_ANDROID)
	/* register our signal handlers */
	{
		struct sigaction sig_action = {};
		sig_action.sa_sigaction = &RunExceptionHandler;
		sigemptyset(&sig_action.sa_mask);

		static char stack[SIGSTKSZ];
		stack_t ss = {
			.ss_size = SIGSTKSZ,
			.ss_sp = stack,
			.ss_flags = 0
		};

		sigaltstack(&ss, NULL);

		#ifdef __APPLE__
		/* for some reason we backtrace() doesn't work on osx
		   when we use an alternate stack */
		sig_action.sa_flags = SA_SIGINFO | SA_RESETHAND;
		#else
		sig_action.sa_flags = SA_SIGINFO | SA_ONSTACK | SA_RESETHAND;
		#endif

		for (int i = 0; i < _countof(installedSignalArray); i++)
			sigaction(installedSignalArray[i], &sig_action, oldSignalActionArray + i);
	}
	#endif
	
	// Detour
	#if defined(IS_PLATFORM_WIN_X86) || defined(IS_PLATFORM_WIN_X64)
	{
		// GTA V may have protection against function redirection.
		// Unsure. Maybe GTA V 1.0.335.2 has protection and newer versions do not.
		
		if (!CGameVersion::IsAny_GTA_V(gameVersion))
		{
			MH_CreateHook(&CreateFileW, &DetouredCreateFileW, (void**)&RealCreateFileW);
			MH_EnableHook(&CreateFileW);

			MH_CreateHook(&CreateFileA, &DetouredCreateFileA, (void**)&RealCreateFileA);
			MH_EnableHook(&CreateFileA);
			
			MH_CreateHook(&LoadLibraryA, &DetouredLoadLibraryA, (void**)&RealLoadLibrary);
			MH_EnableHook(&LoadLibraryA);
		}

		void* pSetUnhandledExceptionFilter = &SetUnhandledExceptionFilter;

		// GTA V has got a protection against modification
		if (CGameVersion::IsAny_GTA_V(gameVersion))
		{
			HMODULE kernelBase = GetModuleHandleA("KERNELBASE.dll");
			
			pSetUnhandledExceptionFilter = GetProcAddress(kernelBase, "SetUnhandledExceptionFilter");
		}

		MH_CreateHook(pSetUnhandledExceptionFilter, &DetouredSetUnhandledExceptionFilter, NULL);
		MH_EnableHook(pSetUnhandledExceptionFilter);

		/////////////

		static const uint8_t func_ret_1[] = 
		{
			0xB8,	// mov
			0x01, 0x00, 0x00, 0x00,	// 1

			0xC3	// retn
		};


		MAKE_DEAD_IF();
			#ifdef IS_PLATFORM_WIN_X86
			else if (gameVersion == GAME_VERSION_GTA_VC_1_0_WIN_X86)
				CPatch::PatchMemoryData(g_mCalc.GetCurrentVAbyPreferedVA(0x677E40), func_ret_1, sizeof(func_ret_1));
			else if (gameVersion == GAME_VERSION_BULLY_SE_1_2_WIN_X86)
				CPatch::PatchMemoryData(g_mCalc.GetCurrentVAbyPreferedVA(0x861850), func_ret_1, sizeof(func_ret_1));
			#elif defined(IS_PLATFORM_WIN_X64)
			//else if (gameVersion == GAME_VERSION_GTA_TRILOGY_SA_1_0_0_14388_WIN_X64)
			//	CPatch::PatchMemoryData(g_mCalc.GetCurrentVAbyPreferedVA(0x141903130), func_ret_1, sizeof(func_ret_1));


		/*  

		__int64 __fastcall sub_141903130(int a1)
	{
	  __int64 v2; // rax
	  int v3; // edx
	  int v4; // er8
	  int v5; // er9

	  if ( byte_1454EF300 )
	  {
		v2 = sub_14190FEB0();
		if ( *(_QWORD *)(v2 + 64) && (unsigned __int8)sub_141913FB0(v2 + 64) )
		{
		  if ( !(unsigned __int8)sub_1418FEAD0() )
			sub_1417C8D30();
		  sub_141900460(a1, v3, v4, v5);
		}
		ExitProcess(0xBDB2Eu);
	  }
	  return 0i64;
	}

		*/
		
		#endif
	}
	#endif

	GlobalExceptionHandler::bIsExceptionHandlerRegistered = true;
	
	CGenericLogStorage::SaveTextLn("Global exception handler has been registered.");

	/////////////
	// CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x3F3FB2), (void*)0x65);
	//CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x3F3FB2), 0xde00);

	//OutputFormattedDebugString("crash!!!");
	 // *(int*)0x6677 = 5;
	//OutputFormattedDebugString("after crash");

	// make a crash
	// 0x748710 = winmain
	// CPatch::PatchUINT32(0x748710, 5323242);
	// CPatch::RedirectCode(0x748710, &patch_test);

	// CPatch::PatchMemoryData(0x4F1290, "\xA1\x00\x00\x00\x00", 5);

	// GTA IV
	// CPatch::RedirectCode(0xBE6FB0, &patch_test);
}

// Disables music playing
void GlobalExceptionHandler::DisableMusicPlaying(bool bDisable)
{
	GlobalExceptionHandler::bDisableMusicPlaying = bDisable;
}

// Print to variables
void GlobalExceptionHandler::PrintfToBuffer(tExceptionInfoPrinting* pPrinting, bool bPrintToFile, bool bPrintToMsgBox, const char* format, ...)
{
	va_list vl;
	va_start(vl, format);

	char buffer[4096];

	vsnprintf(buffer, sizeof(buffer), format, vl);

	if(bPrintToFile)
		CGenericLogStorage::SaveText(buffer);

	if(bPrintToMsgBox)
	{
		pPrinting->msgBoxStr += buffer;

		/*
		strcpy(
			pPrinting->msgBoxStr + pPrinting->msgBoxOffset,
			buffer
			);

		pPrinting->msgBoxOffset += l;
		*/
	}

	va_end(vl);
}

// Prints the exception address
void GlobalExceptionHandler::PrintExceptionAddress(tExceptionInfoPrinting* pPrinting, uintptr_t exceptionAddress, const char* exceptionModuleAddressStr)
{
	PrintfToBuffer(
		pPrinting, true, true, "\nException address: 0x" PRINTF_POINTER_HEX_STR_PAD " (%s)",
		exceptionAddress,
		exceptionModuleAddressStr
	);
}

// Prints an information about screenshot
void GlobalExceptionHandler::PrintInformationAboutScreenshot(tExceptionInfoPrinting* pPrinting)
{
	PrintfToBuffer(pPrinting, false, true, "\n\nPlease do not take a screenshot, but send a full log file to others!");
}


void GlobalExceptionHandler::PrintStackDump(tExceptionInfoPrinting* pPrinting, tExceptionInfo* pExceptionInfo)
{
	const bool bPrintToFile = true;
	const bool bPrintToMsgBox = false;
	uintptr_t base, bottom, top;

	const unsigned int word_size = sizeof(void*);

	unsigned int sizeToPrint = 0x140;

	if (word_size == 8)
		sizeToPrint *= 2;

	#if IS_PLATFORM_WIN
	EXCEPTION_POINTERS* ep = pExceptionInfo->ep;

	// We need the ESP of the exception context to execute a stack dump, make sure we have access to it
	// Seen at ModLoader source code
	if ((ep->ContextRecord->ContextFlags & CONTEXT_CONTROL) == 0)
		return;	

	#if IS_PLATFORM_WIN_X86
	top = (uintptr_t)pExceptionInfo->ep->ContextRecord->Esp;
	#elif defined(IS_PLATFORM_WIN_X64)
	top = (uintptr_t)pExceptionInfo->ep->ContextRecord->Rsp;
	#else
	return;
	#endif

	MEMORY_BASIC_INFORMATION mbi;	

	// Finds the bottom of the stack from it's base pointer
	// Note: mbi will get overriden on this function
	auto GetStackBottom = [&mbi](uintptr_t base)
	{
		VirtualQuery((void*)base, &mbi, sizeof(mbi));                               // Find uncommited region of the stack
		VirtualQuery((char*)mbi.BaseAddress + mbi.RegionSize, &mbi, sizeof(mbi));   // Find guard page
		VirtualQuery((char*)mbi.BaseAddress + mbi.RegionSize, &mbi, sizeof(mbi));   // Find commited region of the stack
		auto last = (uintptr_t)mbi.BaseAddress;
		return (base + (last - base) + mbi.RegionSize);                             // base + distanceToLastRegion + lastRegionSize
	};
	
	// Makes sure the pointer at top (ESP) is valid and readable memory
	if (!VirtualQuery((void*)(top), &mbi, sizeof(mbi))
		&& (mbi.State & MEM_COMMIT)
		&& (mbi.Protect & (PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_READWRITE | PAGE_READONLY)) != 0)
		return;
	
	base = (uintptr_t)mbi.AllocationBase;          // Base of the stack (uncommited)
	bottom = GetStackBottom(base);                  // Bottom of the stack (commited)
	#elif defined IS_PLATFORM_ANDROID
	{
		#ifdef IS_ARCHITECTURE_ARM32
		top = pExceptionInfo->context->uc_mcontext.arm_sp;
		#elif IS_ARCHITECTURE_ARM64
		top = pExceptionInfo->context->uc_mcontext.sp;
		#elif IS_ARCHITECTURE_X86
		top = pExceptionInfo->context->uc_mcontext.gregs[REG_ESP];
		#elif IS_ARCHITECTURE_X64
		top = pExceptionInfo->context->uc_mcontext.gregs[REG_RSP];
		#else
		return;
		#endif

		bool bStackFound = false;

		for (const tMemoryRegionInformation& region : ListOfMemoryRegions)
		{
			if (top >= (uintptr_t)region.start && top <= (uintptr_t)region.end)
			{
				base = (uintptr_t)region.start;
				bottom = (uintptr_t)region.end;

				bStackFound = region.permissions[0] == 'r';
				break;				
			}
		}

		if (!bStackFound)
			return;
	}
	#else
	return;
	#endif

	// Align the stack top (esp) in a 4 bytes boundary
	auto remainder = top % word_size;
	uintptr_t start_pointer = remainder ? top + (word_size - remainder) : top;
	uintptr_t current = start_pointer;

	auto endStackPointer = current + sizeToPrint;

	if (endStackPointer > bottom)
	{
		endStackPointer = bottom;
		// printf_MessageBox("current: 0x%X endStackPointer: 0x%X bottom: 0x%X", current, endStackPointer, bottom);
	}

	PrintfToBuffer(pPrinting, bPrintToFile, bPrintToMsgBox, "\n\nStack (printing from 0x%llX):", (uint64_t)start_pointer);

	unsigned int numberOfBytesPrintedInLine = 0;

	while (current < endStackPointer)	// number of lines
	{
		uint32_t offset = (uintptr_t)current - (uintptr_t)start_pointer;

		if (numberOfBytesPrintedInLine == 0)
			PrintfToBuffer(pPrinting, bPrintToFile, bPrintToMsgBox, "\n+0x%03X", offset);

		PrintfToBuffer(pPrinting, bPrintToFile, bPrintToMsgBox, " ");

		for (unsigned int j = 0; j < word_size; j++)
			PrintfToBuffer(pPrinting, bPrintToFile, bPrintToMsgBox,
				" %02X",
				*(uint8_t*)(current + j)
			);

		current += word_size;
		numberOfBytesPrintedInLine += word_size;

		if (numberOfBytesPrintedInLine == 16)
			numberOfBytesPrintedInLine = 0;
	}

	PrintfToBuffer(
		pPrinting,
		bPrintToFile,
		bPrintToMsgBox,
		"\n\nbase: 0x%llX   top: 0x%llX   bottom: 0x%llX",
		(uint64_t)base, (uint64_t)top, (uint64_t)bottom
	);
}

#if IS_PLATFORM_WIN
HHOOK hHook = NULL;

LRESULT CALLBACK CBTHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode == HCBT_CREATEWND)
    {
        HWND hMsgBox = (HWND) wParam;
        LONG_PTR style = GetWindowLongPtr(hMsgBox, GWL_STYLE);
        SetWindowLongPtr(hMsgBox, GWL_STYLE, style & ~WS_SYSMENU);
    }

    return CallNextHookEx(hHook, nCode, wParam, lParam);
}

// Exception handler
LONG CALLBACK GlobalExceptionHandler::RunExceptionHandler(EXCEPTION_POINTERS* ep)
{
	// stop it
	// while(*(BYTE*)0x748703 == 0x90);		

	// Fix the FPU
	_fpreset();

	tExceptionInfo exceptionInfo;
	exceptionInfo.ep = ep;

	// Enter critical section for generating the crashlog
	EnterCriticalSection(&crashCriticalSection);

	tExceptionInfoPrinting printing;
	printing.Init();

	#ifdef IS_ARCHITECTURE_X86
	uintptr_t instructionPointer = ep->ContextRecord->Eip;
	#define PLATFORM_SPECIFIC_VARS_DEFINED
	#elif defined(IS_ARCHITECTURE_X64)
	uintptr_t instructionPointer = ep->ContextRecord->Rip;
	#elif defined(IS_ARCHITECTURE_ARM32) || defined(IS_ARCHITECTURE_ARM64)
	uintptr_t instructionPointer = ep->ContextRecord->Pc;
	#endif

	DWORD exceptionCode = ep->ExceptionRecord->ExceptionCode;
	PVOID exceptionAddress = ep->ExceptionRecord->ExceptionAddress;
	const char* exceptionCodeName = GlobalExceptionHandler::GetExceptionName(exceptionCode);

	if (exceptionCodeName == NULL)
		exceptionCodeName = "UNKNOWN";

	PrintfToBuffer(&printing, true, false, "\n\n");
	PrintfToBuffer(&printing, true, true, "Game has crashed, here's a crash log:");

	DWORD processID = GetCurrentProcessId();
	DWORD threadID = GetCurrentThreadId();

	HANDLE hProcess = GetCurrentProcess();	

	PrintfToBuffer(&printing, true, true, "\nCurrent process ID: %lu", processID);
	PrintfToBuffer(&printing, true, true, "\nCurrent thread ID: %lu", threadID);

	PrintfToBuffer(&printing, true, true,
		"\nLast file to be loaded: %s",

		*GlobalExceptionHandler::ms_LastFileLoaded ?
		GlobalExceptionHandler::ms_LastFileLoaded : "NOT SET"
		);
	PrintfToBuffer(&printing, true, true,
		"\nLast library loaded: %s",

		*GlobalExceptionHandler::ms_LastLibraryLoaded ?
		GlobalExceptionHandler::ms_LastLibraryLoaded : "NOT SET"
		);

	// Enumerate modules
	char exceptionModuleAddressStr[MAX_PATH] = "module not found";
	char instructionPointerAddressStr[MAX_PATH] = "module not found";

	{
		HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, NULL);

		if (snapshot != INVALID_HANDLE_VALUE)
		{
			MODULEENTRY32 entry;
			entry.dwSize = sizeof(entry);

			bool bHasExceptionModuleBeenFound = false;
			bool bHasInstructionPointerModuleBeenFound = false;

			bool bIsModuleInfoRead = Module32First(snapshot, &entry) != 0;

			while (bIsModuleInfoRead)
			{
				/*
				printf_MessageBox(
					"entry.szModule: %s entry.modBaseAddr: 0x%X entry.modBaseSize: 0x%X\n",
					entry.szModule,
					entry.modBaseAddr,
					entry.modBaseSize
					);
				*/

				if (!bHasExceptionModuleBeenFound
					&& exceptionAddress >= entry.modBaseAddr
					&& exceptionAddress < entry.modBaseAddr + entry.modBaseSize)
				{
					bHasExceptionModuleBeenFound = true;

					snprintf(exceptionModuleAddressStr, sizeof(exceptionModuleAddressStr),
						"\"%s\"+0x" PRINTF_POINTER_HEX_STR,
						entry.szModule,
						((BYTE*)exceptionAddress - entry.modBaseAddr));

					if (bHasExceptionModuleBeenFound && bHasInstructionPointerModuleBeenFound)
						break;
				}

				if (!bHasInstructionPointerModuleBeenFound
					&& (BYTE*)instructionPointer >= entry.modBaseAddr
					&& (BYTE*)instructionPointer < entry.modBaseAddr + entry.modBaseSize)
				{
					bHasInstructionPointerModuleBeenFound = true;

					sprintf_s(instructionPointerAddressStr, sizeof(instructionPointerAddressStr),
						"\"%s\"+0x" PRINTF_POINTER_HEX_STR,
						entry.szModule,
						((BYTE*)instructionPointer - entry.modBaseAddr));

					if (bHasExceptionModuleBeenFound && bHasInstructionPointerModuleBeenFound)
						break;
				}

				bIsModuleInfoRead = Module32Next(snapshot, &entry) != 0;
			}

			CloseHandle(snapshot);
		}
		else
		{
			strcpy(exceptionModuleAddressStr, "Error: snapshot = INVALID_HANDLE_VALUE");
			strcpy(instructionPointerAddressStr, exceptionModuleAddressStr);
		}
	}

	// Exception address
	PrintExceptionAddress(&printing, (uintptr_t)exceptionAddress, exceptionModuleAddressStr);

	// Exception code
	PrintfToBuffer(&printing, true, true, "\nException code: 0x%X (%s)", exceptionCode, exceptionCodeName);
	
	if (exceptionCode == EXCEPTION_ACCESS_VIOLATION || exceptionCode == EXCEPTION_IN_PAGE_ERROR)
		PrintfToBuffer(&printing,
			true,
			true,
			"\nInaccessible memory address: 0x" PRINTF_POINTER_HEX_STR,
			ep->ExceptionRecord->ExceptionInformation[1]
		);

	// General registers
	#ifdef IS_ARCHITECTURE_X86
	PrintfToBuffer(&printing, true, true,
		"\n\nGeneral registers:"
		"\nEAX: 0x%08X (%d)"
		"\nEBX: 0x%08X (%d)"
		"\nECX: 0x%08X (%d)"
		"\nEDX: 0x%08X (%d)"
		"\nESI: 0x%08X (%d)"
		"\nEDI: 0x%08X (%d)"
		"\nEBP: 0x%08X (%d)"
		"\nESP: 0x%08X (%d)"
		"\nEIP: 0x%08X (%d) [%s]"
		"\nEFL: 0x%08X (%d)",

		ep->ContextRecord->Eax, ep->ContextRecord->Eax,
		ep->ContextRecord->Ebx, ep->ContextRecord->Ebx,
		ep->ContextRecord->Ecx, ep->ContextRecord->Ecx,
		ep->ContextRecord->Edx, ep->ContextRecord->Edx,
		ep->ContextRecord->Esi, ep->ContextRecord->Esi,
		ep->ContextRecord->Edi, ep->ContextRecord->Edi,
		ep->ContextRecord->Ebp, ep->ContextRecord->Ebp,
		ep->ContextRecord->Esp, ep->ContextRecord->Esp,
		ep->ContextRecord->Eip, ep->ContextRecord->Eip, instructionPointerAddressStr,
		ep->ContextRecord->EFlags, ep->ContextRecord->EFlags
		);
	#elif defined(IS_ARCHITECTURE_X64)
	PrintfToBuffer(&printing, true, true,
		"\n\nGeneral registers:"
		"\nRAX: 0x%016llX (%lld)"
		"\nRBX: 0x%016llX (%lld)"
		"\nRCX: 0x%016llX (%lld)"
		"\nRDX: 0x%016llX (%lld)"
		"\nRSI: 0x%016llX (%lld)"
		"\nRDI: 0x%016llX (%lld)"
		"\nRBP: 0x%016llX (%lld)"
		"\nRSP: 0x%016llX (%lld)"
		"\nRIP: 0x%016llX (%lld) [%s]"

		"\nR8:  0x%016llX (%lld)"
		"\nR9:  0x%016llX (%lld)"
		"\nR10: 0x%016llX (%lld)"
		"\nR11: 0x%016llX (%lld)"
		"\nR12: 0x%016llX (%lld)"
		"\nR13: 0x%016llX (%lld)"
		"\nR14: 0x%016llX (%lld)"
		"\nR15: 0x%016llX (%lld)"

		"\nEFL: 0x%08X         (%d)",

		ep->ContextRecord->Rax, ep->ContextRecord->Rax,
		ep->ContextRecord->Rbx, ep->ContextRecord->Rbx,
		ep->ContextRecord->Rcx, ep->ContextRecord->Rcx,
		ep->ContextRecord->Rdx, ep->ContextRecord->Rdx,
		ep->ContextRecord->Rsi, ep->ContextRecord->Rsi,
		ep->ContextRecord->Rdi, ep->ContextRecord->Rdi,
		ep->ContextRecord->Rbp, ep->ContextRecord->Rbp,
		ep->ContextRecord->Rsp, ep->ContextRecord->Rsp,
		ep->ContextRecord->Rip, ep->ContextRecord->Rip, instructionPointerAddressStr,

		ep->ContextRecord->R8, ep->ContextRecord->R8,
		ep->ContextRecord->R9, ep->ContextRecord->R9,
		ep->ContextRecord->R10, ep->ContextRecord->R10,
		ep->ContextRecord->R11, ep->ContextRecord->R11,
		ep->ContextRecord->R12, ep->ContextRecord->R12,
		ep->ContextRecord->R13, ep->ContextRecord->R13,
		ep->ContextRecord->R14, ep->ContextRecord->R14,
		ep->ContextRecord->R15, ep->ContextRecord->R15,

		ep->ContextRecord->EFlags, ep->ContextRecord->EFlags
		);
	#else
	PrintfToBuffer(&printing, true, true, "\n");
	#endif

	// Information
	PrintInformationAboutScreenshot(&printing);

	// Segment registers
	#if defined(IS_ARCHITECTURE_X86) || defined(IS_ARCHITECTURE_X64)
	PrintfToBuffer(&printing, true, false,
		"\n\nSegment registers:"
		"\nCS: %04X"
		"\nDS: %04X"
		"\nES: %04X"
		"\nFS: %04X"
		"\nGS: %04X"
		"\nSS: %04X",

		ep->ContextRecord->SegCs,
		ep->ContextRecord->SegDs,
		ep->ContextRecord->SegEs,
		ep->ContextRecord->SegFs,
		ep->ContextRecord->SegGs,
		ep->ContextRecord->SegSs
		);
	#endif

	// FPU registers
	#ifdef IS_PLATFORM_WIN_X86
	PrintfToBuffer(&printing, true, false, "\n\nFPU registers:");

	for (int i = 0; i < 8; i++)
	{
		PrintfToBuffer(&printing, true, false,
			"\nST%d: %lf bytes:",
			i,
			ReadLongDouble(ep->ContextRecord->FloatSave.RegisterArea + i * 10)
			);

		// ST register bytes
		BYTE* pSTvalue = ep->ContextRecord->FloatSave.RegisterArea + 10 * i;

		for (int i = 0; i < 10; i++)
			PrintfToBuffer(&printing, true, false, " %02X", pSTvalue[i]);
	}

	PrintfToBuffer(&printing, true, false,
		"\nCTRL: %04X"
		"\nSTAT: %04X"
		"\nTAGS: %04X",

		ep->ContextRecord->FloatSave.ControlWord,
		ep->ContextRecord->FloatSave.StatusWord,
		ep->ContextRecord->FloatSave.TagWord
		);
	#endif	

	// MMX registers
	#ifdef IS_PLATFORM_WIN_X86
	PrintfToBuffer(&printing, true, false, "\n\nMMX registers, 8 bytes:");

	for (int i = 0; i < 8; i++)
	{
		PrintfToBuffer(&printing, true, false, "\nMM%d:", i);

		// MMX 8 bytes
		BYTE* pMMXvalue = ep->ContextRecord->FloatSave.RegisterArea + 10 * i;

		for (int i = 0; i < 8; i++)
			PrintfToBuffer(&printing, true, false, " %02X", pMMXvalue[i]);
	}
	#endif

	// XMM registers
	#ifdef IS_PLATFORM_WIN_X86
	PrintfToBuffer(&printing, true, false, "\n\nXMM registers, 16 bytes:");

	for (int i = 0; i < 8; i++)
	{
		PrintfToBuffer(&printing, true, false, "\nXMM%d:", i);

		// XMM registers are placed offset +160
		BYTE* pXMMvalue = ep->ContextRecord->ExtendedRegisters + 160;

		// XMM 16 bytes
		for (int i = 0; i < 16; i++)
			PrintfToBuffer(&printing, true, false, " %02X", pXMMvalue[i]);
	}
	#endif

	// Stack dump
	PrintStackDump(&printing, &exceptionInfo);
	
	// Module list
	PrintfToBuffer(&printing, true, false, "\n\nModule list\n; Path\tModule file size\t\tBase\tSize of image\tEntry point");

	DWORD cbNeeded;
	HMODULE hMods[1024];

	if(EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded))
	{
		DWORD numberOfModules = cbNeeded / sizeof(HMODULE);

		char modulePath[1024];

		MODULEINFO moduleInfo;

		for(unsigned int i = 0; i < numberOfModules; i++)
		{
			HMODULE hModule = hMods[i];	

			GetModuleFileNameA(hModule, modulePath, sizeof(modulePath));

			__int64 moduleFilesize = GetFileSize(modulePath);

			GetModuleInformation(hProcess, hModule, &moduleInfo, sizeof(moduleInfo));

			PrintfToBuffer(
				&printing,
				true,
				false,
				"\n%s\t%lld\t"
				"0x" PRINTF_POINTER_HEX_STR_PAD
				"\t0x%08X\t"
				"0x" PRINTF_POINTER_HEX_STR_PAD,
				modulePath,
				moduleFilesize,
				moduleInfo.lpBaseOfDll,
				moduleInfo.SizeOfImage,
				moduleInfo.EntryPoint
			);
		}
	}
	else
		PrintfToBuffer(&printing, true, false, "\nError while retrieving a list of modules!");

	//////////////////////////////////////////////////

	CGenericLogStorage::SaveWorkBuffer();

	hHook = SetWindowsHookEx(WH_CBT, (HOOKPROC)CBTHookProc, NULL, GetCurrentThreadId());

#ifndef MAKE_A_LITE_VERSION
	if (!GlobalExceptionHandler::bDisableMusicPlaying)
		PlaySoundA(
			MAKEINTRESOURCEA(GLOBAL_EXCEPTION_HANDLER_MUSIC),
			g_LimitAdjuster.hModule_of_the_FLA.windows,
			SND_RESOURCE | SND_ASYNC | SND_LOOP
		);
#endif

	// Leave critical section, no more data are written to log file
	LeaveCriticalSection(&crashCriticalSection);

	// Show a message box
	// while(true)
		printf_MessageBox(printing.msgBoxStr.c_str());

	UnhookWindowsHookEx(hHook);

	g_LimitAdjuster.TerminateProcess();
	return EXCEPTION_EXECUTE_HANDLER;
}
#endif

#ifdef IS_PLATFORM_ANDROID
// Exception handler
void GlobalExceptionHandler::RunExceptionHandler(int sig, siginfo_t *siginfo, void *context)
{
	ucontext_t *Context = (ucontext_t *)context;

	tExceptionInfo exceptionInfo;	
	exceptionInfo.sig = sig;
	exceptionInfo.siginfo = siginfo;
	exceptionInfo.context = Context;

	tExceptionInfoPrinting printing;
	printing.Init();
	
	#if defined(IS_ARCHITECTURE_ARM32)
	uintptr_t instructionPointer = Context->uc_mcontext.arm_pc;
	auto exceptionAddress = Context->uc_mcontext.fault_address;
	#define PLATFORM_SPECIFIC_VARS_DEFINED
	#elif defined(IS_ARCHITECTURE_ARM64)
	uintptr_t instructionPointer = Context->uc_mcontext.pc;
	auto exceptionAddress = Context->uc_mcontext.fault_address;
	#define PLATFORM_SPECIFIC_VARS_DEFINED
	#elif defined(IS_ARCHITECTURE_X86)
	uintptr_t instructionPointer = Context->uc_mcontext.gregs[REG_EIP];
	auto exceptionAddress = Context->uc_mcontext.gregs[REG_ERR];
	#define PLATFORM_SPECIFIC_VARS_DEFINED
	#elif defined(IS_ARCHITECTURE_X64)
	uintptr_t instructionPointer = Context->uc_mcontext.gregs[REG_RIP];
	auto exceptionAddress = Context->uc_mcontext.gregs[REG_RIP];
	#define PLATFORM_SPECIFIC_VARS_DEFINED
	#endif

	int exceptionCode = siginfo->si_code;
	const char* exceptionSignalName;
	const char* exceptionCodeName;

	GlobalExceptionHandler::GetExceptionName(sig, exceptionCode, &exceptionSignalName, &exceptionCodeName);
	
	if (exceptionSignalName == NULL)
		exceptionSignalName = "UNKNOWN";

	if (exceptionCodeName == NULL)
		exceptionCodeName = "UNKNOWN";

	PrintfToBuffer(&printing, true, false, "\n\n");
	PrintfToBuffer(&printing, true, true, "Application has crashed, here's a log:");
	
	pid_t processID = getpid();
	pid_t threadID = gettid();

	PrintfToBuffer(&printing, true, true, "\nCurrent process ID: %lu", (int)processID);
	PrintfToBuffer(&printing, true, true, "\nCurrent thread ID: %lu", (int)threadID);
	
	// Enumerate memory regions
	tMemoryRegionInformation tmpRegion;

	char exceptionModuleAddressStr[256] = "module not found";
	char instructionPointerAddressStr[256] = "module not found";
	
	ListOfMemoryRegions.clear();

	{
		#ifdef PLATFORM_SPECIFIC_VARS_DEFINED
		bool bHasExceptionRegionBeenFound = false;
		bool bHasInstructionRegionBeenFound = false;
		#endif

		FILE* fp = fopen("/proc/self/maps", "r");

		if (fp)
		{
			char line[1024];
			fseek(fp, 0, SEEK_END);

			while (fgets(line, sizeof(line), fp))
			{
				char* bySpace;
				char* pAddresses = strtok_s(line, " ", &bySpace);

				if (pAddresses != NULL)
				{
					char* perms = strtok_s(NULL, " ", &bySpace);

					if (perms)
					{
						char* offset = strtok_s(NULL, " ", &bySpace);

						if (offset)
						{
							char* dev = strtok_s(NULL, " ", &bySpace);
							
							if (dev)
							{
								char* inode = strtok_s(NULL, " ", &bySpace);

								if (inode)
								{
									char* pathname = strtok_s(NULL, " ", &bySpace);
									TrimRight(pathname);

									//////
									strncpy(tmpRegion.permissions, perms, sizeof(tmpRegion.permissions));

									sscanf(
										pAddresses,
										PRINTF_POINTER_HEX_STR "-" PRINTF_POINTER_HEX_STR,
										&tmpRegion.start, &tmpRegion.end
									);

									tmpRegion.pathname = pathname;

									#if defined(PLATFORM_SPECIFIC_VARS_DEFINED) && FALSE
									if (!bHasExceptionRegionBeenFound
										&& exceptionAddress >= (uintptr_t)tmpRegion.start
										&& exceptionAddress <= (uintptr_t)tmpRegion.end)
									{
										bHasExceptionRegionBeenFound = true;
										snprintf(exceptionModuleAddressStr, sizeof(exceptionModuleAddressStr),
											"\"%s\"+0x" PRINTF_POINTER_HEX_STR,
											pathname,
											((char*)exceptionAddress - (char*)tmpRegion.start)
										);
									}
									
									if (!bHasInstructionRegionBeenFound
										&& instructionPointer >= (uintptr_t)tmpRegion.start
										&& instructionPointer <= (uintptr_t)tmpRegion.end)
									{
										bHasInstructionRegionBeenFound = true;

										snprintf(instructionPointerAddressStr, sizeof(instructionPointerAddressStr),
											"\"%s\"+0x" PRINTF_POINTER_HEX_STR,
											pathname,
											((char*)instructionPointer - (char*)tmpRegion.start)
										);
									}
									#endif

									ListOfMemoryRegions.push_back(tmpRegion);
								}
							}
						}
					}					
				}
			}

			fclose(fp);
		}

		/////////
		Dl_info address_info;

		if (dladdr((void*)exceptionAddress, &address_info))
		{
			if(address_info.dli_fname)
				snprintf(exceptionModuleAddressStr, sizeof(exceptionModuleAddressStr),
					"\"%s\"+0x" PRINTF_POINTER_HEX_STR,
					GetFilenameFromPath(address_info.dli_fname),
					((char*)exceptionAddress - (char*)address_info.dli_fbase)
				);
		}

		if (dladdr((void*)instructionPointer, &address_info))
		{
			if (address_info.dli_fname)
				snprintf(instructionPointerAddressStr, sizeof(instructionPointerAddressStr),
					"\"%s\"+0x" PRINTF_POINTER_HEX_STR,
					GetFilenameFromPath(address_info.dli_fname),
					((char*)instructionPointer - (char*)address_info.dli_fbase)
				);
		}
	}

	// Exception address
	#ifdef PLATFORM_SPECIFIC_VARS_DEFINED	
	PrintExceptionAddress(&printing, (uintptr_t)exceptionAddress, exceptionModuleAddressStr);
	#endif

	PrintfToBuffer(&printing, true, true, "\nException signal: %d (%s)", sig, exceptionSignalName);
	PrintfToBuffer(&printing, true, true, "\nException code: 0x%X (%s)", exceptionCode, exceptionCodeName);

	// General registers
	#ifdef IS_ARCHITECTURE_ARM32
	PrintfToBuffer(&printing, true, true,
		"\n\nGeneral registers:"
		"\nR0 : 0x%08X (%d)"
		"\nR1 : 0x%08X (%d)"
		"\nR2 : 0x%08X (%d)"
		"\nR3 : 0x%08X (%d)"
		"\nR4 : 0x%08X (%d)"
		"\nR5 : 0x%08X (%d)"
		"\nR6 : 0x%08X (%d)"
		"\nR7 : 0x%08X (%d)"
		"\nR8 : 0x%08X (%d)"
		"\nR9 : 0x%08X (%d)"
		"\nR10: 0x%08X (%d)"
		"\nR11: 0x%08X (%d)"
		"\nR12: 0x%08X (%d)"
		"\nSP : 0x%08X (%d)"
		"\nLR : 0x%08X (%d)"
		"\nPC : 0x%08X (%d) [%s]"
		"\nPSR : 0x%08X (%d)"		
		,
		Context->uc_mcontext.arm_r0, Context->uc_mcontext.arm_r0,
		Context->uc_mcontext.arm_r1, Context->uc_mcontext.arm_r1,
		Context->uc_mcontext.arm_r2, Context->uc_mcontext.arm_r2,
		Context->uc_mcontext.arm_r3, Context->uc_mcontext.arm_r3,
		Context->uc_mcontext.arm_r4, Context->uc_mcontext.arm_r4,
		Context->uc_mcontext.arm_r5, Context->uc_mcontext.arm_r5,
		Context->uc_mcontext.arm_r6, Context->uc_mcontext.arm_r6,
		Context->uc_mcontext.arm_r7, Context->uc_mcontext.arm_r7,
		Context->uc_mcontext.arm_r8, Context->uc_mcontext.arm_r8,
		Context->uc_mcontext.arm_r9, Context->uc_mcontext.arm_r9,
		Context->uc_mcontext.arm_r10, Context->uc_mcontext.arm_r10,
		Context->uc_mcontext.arm_fp, Context->uc_mcontext.arm_fp,	// R11
		Context->uc_mcontext.arm_ip, Context->uc_mcontext.arm_ip,	// R12
		Context->uc_mcontext.arm_sp, Context->uc_mcontext.arm_sp,	// SP
		Context->uc_mcontext.arm_lr, Context->uc_mcontext.arm_lr,	// LR
		Context->uc_mcontext.arm_pc, Context->uc_mcontext.arm_pc, instructionPointerAddressStr,	// PC
		Context->uc_mcontext.arm_cpsr, Context->uc_mcontext.arm_cpsr	// PSR
	);
	#else
	PrintfToBuffer(&printing, true, true, "\n");
	#endif

	// Information
	PrintInformationAboutScreenshot(&printing);

	// Stack dump
	PrintStackDump(&printing, &exceptionInfo);

	// Memory region list
	if(false)	// disable it
	{
		PrintfToBuffer(&printing, true, false, "\n\nMemory map\n; Start     End         Perm  Path");

		for(const tMemoryRegionInformation& region : ListOfMemoryRegions)
		{
			PrintfToBuffer(
				&printing,
				true,
				false,
				"\n"
				"0x" PRINTF_POINTER_HEX_STR_PAD
				"  0x" PRINTF_POINTER_HEX_STR_PAD
				"  %s  %s",
				region.start,
				region.end,
				region.permissions,
				region.pathname.c_str()
			);
		}
	}

	// Show a message box
	printf_MessageBox(printing.msgBoxStr.c_str());

	// Call old handler
	struct sigaction* pOldAction = GetPointerToOldSigAction(sig);
	
	if (pOldAction->sa_flags & SA_SIGINFO)
	{
		if (pOldAction->sa_sigaction)
			pOldAction->sa_sigaction(sig, siginfo, context);
	}
	else
	{
		if (pOldAction->sa_handler != SIG_DFL && pOldAction->sa_handler != SIG_IGN && pOldAction->sa_handler != SIG_ERR)
			pOldAction->sa_handler(sig);
	}

	// Finish
	CGenericLogStorage::SaveWorkBuffer();
}
#endif

#if IS_PLATFORM_WIN
// Returns exception name by code
const char* GlobalExceptionHandler::GetExceptionName(uint32_t exceptionCode)
{
	switch(exceptionCode)
	{
		case EXCEPTION_ACCESS_VIOLATION:
			return "EXCEPTION_ACCESS_VIOLATION";
		case EXCEPTION_DATATYPE_MISALIGNMENT:
			return "EXCEPTION_DATATYPE_MISALIGNMENT";
		case EXCEPTION_BREAKPOINT:
			return "EXCEPTION_BREAKPOINT";
		case EXCEPTION_SINGLE_STEP:
			return "EXCEPTION_SINGLE_STEP";
		case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
			return "EXCEPTION_ARRAY_BOUNDS_EXCEEDED";
		case EXCEPTION_FLT_DENORMAL_OPERAND:
			return "EXCEPTION_FLT_DENORMAL_OPERAND";
		case EXCEPTION_FLT_DIVIDE_BY_ZERO:
			return "EXCEPTION_FLT_DIVIDE_BY_ZERO";
		case EXCEPTION_FLT_INEXACT_RESULT:
			return "EXCEPTION_FLT_INEXACT_RESULT";
		case EXCEPTION_FLT_INVALID_OPERATION:
			return "EXCEPTION_FLT_INVALID_OPERATION";
		case EXCEPTION_FLT_OVERFLOW:
			return "EXCEPTION_FLT_OVERFLOW";
		case EXCEPTION_FLT_STACK_CHECK:
			return "EXCEPTION_FLT_STACK_CHECK";
		case EXCEPTION_FLT_UNDERFLOW:
			return "EXCEPTION_FLT_UNDERFLOW";
		case EXCEPTION_INT_DIVIDE_BY_ZERO:
			return "EXCEPTION_INT_DIVIDE_BY_ZERO";
		case EXCEPTION_INT_OVERFLOW:
			return "EXCEPTION_INT_OVERFLOW";
		case EXCEPTION_PRIV_INSTRUCTION:
			return "EXCEPTION_PRIV_INSTRUCTION";
		case EXCEPTION_IN_PAGE_ERROR:
			return "EXCEPTION_IN_PAGE_ERROR";
		case EXCEPTION_ILLEGAL_INSTRUCTION:
			return "EXCEPTION_ILLEGAL_INSTRUCTION";
		case EXCEPTION_NONCONTINUABLE_EXCEPTION:
			return "EXCEPTION_NONCONTINUABLE_EXCEPTION";
		case EXCEPTION_STACK_OVERFLOW:
			return "EXCEPTION_STACK_OVERFLOW";
		case EXCEPTION_INVALID_DISPOSITION:
			return "EXCEPTION_INVALID_DISPOSITION";
		case EXCEPTION_GUARD_PAGE:
			return "EXCEPTION_GUARD_PAGE";
		case EXCEPTION_INVALID_HANDLE:
			return "EXCEPTION_INVALID_HANDLE";
		default:
			return NULL;
	}
	
	return NULL;
}
#elif defined(IS_PLATFORM_ANDROID) || defined(IS_PLATFORM_LINUX)
// Returns exception name by code
void GlobalExceptionHandler::GetExceptionName(int sig, int exceptionCode, const char** ppSignalName, const char** ppCodeName)
{
	*ppSignalName = NULL;
	*ppCodeName = NULL;

	if(sig == SIGSEGV)
	{
		*ppSignalName = "SIGSEGV";

		switch (exceptionCode)
		{
		case SEGV_MAPERR:
			*ppCodeName = "SEGV_MAPERR";
			break;
		case SEGV_ACCERR:
			*ppCodeName = "SEGV_ACCERR";
			break;
		default:
			break;
		}
	}
	else if (sig == SIGFPE)
	{
		*ppSignalName = "SIGFPE";

		switch (exceptionCode)
		{
		case FPE_INTDIV:
			*ppCodeName = "FPE_INTDIV";
			break;
		case FPE_INTOVF:
			*ppCodeName = "FPE_INTOVF";
			break;
		case FPE_FLTDIV:
			*ppCodeName = "FPE_FLTDIV";
			break;
		case FPE_FLTOVF:
			*ppCodeName = "FPE_FLTOVF";
			break;
		case FPE_FLTUND:
			*ppCodeName = "FPE_FLTUND";
			break;
		case FPE_FLTRES:
			*ppCodeName = "FPE_FLTRES";
			break;
		case FPE_FLTINV:
			*ppCodeName = "FPE_FLTINV";
			break;
		case FPE_FLTSUB:
			*ppCodeName = "FPE_FLTSUB";
			break;
		default:
			break;
		}
	}
	else if (sig == SIGILL)
	{
		*ppSignalName = "SIGILL";

		switch (exceptionCode)
		{
		case ILL_ILLOPC:
			*ppCodeName = "ILL_ILLOPC";
			break;
		case ILL_ILLOPN:
			*ppCodeName = "ILL_ILLOPN";
			break;
		case ILL_ILLADR:
			*ppCodeName = "ILL_ILLADR";
			break;
		case ILL_ILLTRP:
			*ppCodeName = "ILL_ILLTRP";
			break;
		case ILL_PRVOPC:
			*ppCodeName = "ILL_PRVOPC";
			break;
		case ILL_PRVREG:
			*ppCodeName = "ILL_PRVREG";
			break;
		case ILL_COPROC:
			*ppCodeName = "ILL_COPROC";
			break;
		case ILL_BADSTK:
			*ppCodeName = "ILL_BADSTK";
			break;
		default:
			break;
		}
	}
	else if (sig == SIGBUS)
	{
		*ppSignalName = "SIGBUS";

		switch (exceptionCode)
		{
		case BUS_ADRALN:
			*ppCodeName = "BUS_ADRALN";
			break;
		case BUS_ADRERR:
			*ppCodeName = "BUS_ADRERR";
			break;
		case BUS_OBJERR:
			*ppCodeName = "BUS_OBJERR";
			break;
		default:
			break;
		}
	}
}
#endif

#ifdef IS_PLATFORM_WIN_X86
// Read long double
NAKED long double __cdecl GlobalExceptionHandler::ReadLongDouble(void* pointer)
{
	__asm
	{
		push	ebp;
		mov		ebp, esp;
		mov		eax, pointer;
		fld		tbyte ptr[eax];
		pop		ebp;
		retn;
	}
}
#endif