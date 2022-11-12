/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include <stdint.h>

/*
	Use "volatile" specifier because otherwise NAKED functions with arguments would get passed no arguments on Clang compiler, while calling these functions.
*/

// List of calling conventions
enum eCallingConvention
{
	CALLING_CONVENTION_CDECL,
	CALLING_CONVENTION_STDCALL,
	CALLING_CONVENTION_FASTCALL,
	CALLING_CONVENTION_THISCALL,
};

// Allows to call memory functions
class CMemoryCall
{
public:
	template <typename Ret, typename... Args>
	static Ret FunctionCdecl(uintptr_t address, Args... args) {
		volatile uintptr_t address_ = address;
		return reinterpret_cast<Ret(__cdecl *)(Args...)>(address_)(args...);
	}

	template <typename Ret, typename... Args>
	static Ret FunctionFastCall(uintptr_t address, Args... args) {
		volatile uintptr_t address_ = address;
		return reinterpret_cast<Ret(__fastcall *)(Args...)>(address_)(args...);
	}

	template <typename Ret, typename... Args>
	static Ret FunctionStdCall(uintptr_t address, Args... args) {
		volatile uintptr_t address_ = address;
		return reinterpret_cast<Ret(__stdcall *)(Args...)>(address_)(args...);
	}

	template <typename Ret, typename... Args>
	static Ret Function(uintptr_t address, Args... args) {
		uintptr_t address_ = address;
		return reinterpret_cast<Ret(__cdecl *)(Args...)>(address_)(args...);
	}

	template <typename Ret, typename C, typename... Args>
	static Ret Method(uintptr_t address, C _this, Args... args) {
		volatile uintptr_t address_ = address;
		return reinterpret_cast<Ret(__thiscall *)(C, Args...)>(address_)(_this, args...);
	}
};