/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "../../Core/CLimitAdjusterModule.h"

#include <CRGBA.h>

class CFont
{
public:
	static void SetPropOn();
	static void SetRightJustifyOff();

	// text scaling
	static void SetScale(float w, float h);
	static void SetScale(float w);

	// set text color
	static void SetColor(CRGBA color);

	// setups text background
	static void SetBackground(bool enable, bool includeWrap);
	static void SetBackgroundOff();

	static void SetJustify(unsigned char on);

	// set text style
	static void SetFontStyle(int style);

	static void SetOrientation(unsigned char alignment);

	// set line width at center
	static void SetCentreSize(float value);

	// set line width at right
	static void SetWrapx(float value);

	// Prints a string
	static void PrintString(float x, float y, const void *text);

	// Prints a string
	static void PrintStringBully(float x, float y, const void *text, bool flag);
};

class CFont_VarInitialisation : public CLimitAdjusterModule
{
public:
	// Initialize
	void Initialise();

	// Shutdown
	void Shutdown() {}
};

extern CFont_VarInitialisation g_CFont_varInitialisation;