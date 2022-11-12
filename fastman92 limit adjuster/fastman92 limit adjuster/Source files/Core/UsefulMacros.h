/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include <Assembly/UsefulMacros.h>

// ASM code macros
#if defined(IS_ARCHITECTURE_X86) || defined(IS_ARCHITECTURE_X64)
#define ASM_GET_OFFSET_OF_FLA_MODULE(limitObject) offset [limitObject]

#define ASM_GET_OFFSET_OF_LIMIT_VAR(limitObject, limitType, limitMember) [limitObject + limitType::limitMember]
#define ASM_ACCESS_LIMIT_VAR(limitObject, limitType, limitMember, type) type ptr[limitObject + limitType::limitMember]
#define ASM_ACCESS_LIMIT_VAR_8_BIT(limitObject, limitType, limitMember) ASM_ACCESS_LIMIT_VAR(limitObject, limitType, limitMember, byte)
#define ASM_ACCESS_LIMIT_VAR_16_BIT(limitObject, limitType, limitMember) ASM_ACCESS_LIMIT_VAR(limitObject, limitType, limitMember, word)
#define ASM_ACCESS_LIMIT_VAR_32_BIT(limitObject, limitType, limitMember) ASM_ACCESS_LIMIT_VAR(limitObject, limitType, limitMember, dword)
#define ASM_ACCESS_LIMIT_VAR_64_BIT(limitObject, limitType, limitMember) ASM_ACCESS_LIMIT_VAR(limitObject, limitType, limitMember, qword)
#endif