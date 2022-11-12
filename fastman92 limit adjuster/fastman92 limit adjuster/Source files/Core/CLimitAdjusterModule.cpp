#include "CLimitAdjusterModule.h"

// Constructor
CAllocatedState::CAllocatedState()
{
	this->value = false;
}

// Returns a value;
bool CAllocatedState::Get()
{
	return this->value;
}

// Sets a value
void CAllocatedState::Set(bool value)
{
	this->value = value;
}