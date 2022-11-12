/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

enum ex86registerNum
{
	// 32 bit
	REGISTER_EAX = 0,

	REGISTER_ECX = 1,

	REGISTER_EDX = 2,

	REGISTER_EBX = 3,

	REGISTER_ESP = 4,

	REGISTER_EBP = 5,

	REGISTER_ESI = 6,

	REGISTER_EDI = 7,

	// First 8-bit
	REGISTER_AL = 16,

	REGISTER_CL = 17,

	REGISTER_DL = 18,

	REGISTER_BL = 19,

	// Second 8-bit
	REGISTER_AH = 20,

	REGISTER_CH = 21,

	REGISTER_DH = 22,

	REGISTER_BH = 23,

	// Segment registers
	REGISTER_ES = 29,
	REGISTER_CS = 30,
	REGISTER_SS = 31,
	REGISTER_DS = 32,
	REGISTER_FS = 33,
	REGISTER_GS = 34
};