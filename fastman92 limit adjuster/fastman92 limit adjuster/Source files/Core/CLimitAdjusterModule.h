#pragma once

class CLimitAdjusterModule
{
public:
	// Initialize
	virtual void Initialise() = 0;

	// Shutdown
	virtual void Shutdown() = 0;
};

typedef void(CLimitAdjusterModule::*tLimitMethodInt)(unsigned int iValue);

struct tLimitDefinitionNonStatic {
	const char* property;
	tLimitMethodInt method;
};

class CAllocatedState
{
	bool value;

public:
	// Constructor
	CAllocatedState();

	// Returns a value;
	bool Get();

	// Sets a value
	void Set(bool value);
};

#define DEFINE_IS_ALLOCATED() CAllocatedState bIsAllocated