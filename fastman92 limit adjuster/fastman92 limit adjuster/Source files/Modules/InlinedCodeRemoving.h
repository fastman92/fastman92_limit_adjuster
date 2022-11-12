/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "../Core/CLimitAdjusterModule.h"


enum eInlineRemove
{
	eInlineRemove_CTxdStore__AddTxdSlot,
	eInlineRemove_Max
};

class InlinedCodeRemoving : public CLimitAdjusterModule
{
private:
	bool m_bInlineRemove[eInlineRemove_Max];

public:
	// Initialize
	virtual void Initialise();

	// Shutdown
	virtual void Shutdown() {}

	// Switches action state
	void SwitchHookEnabled(eInlineRemove type, bool bEnable);

	// Returns true if actiom is enabled.
	bool IsHookEnabled(eInlineRemove type);

	// Applies patch of inline removing
	void ApplyHook();
};

extern InlinedCodeRemoving g_InlinedCodeRemoving;