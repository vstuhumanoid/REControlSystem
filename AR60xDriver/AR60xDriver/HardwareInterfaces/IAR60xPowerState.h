#pragma once

#include "../Elements/PowerState.h"

class IAR60xPowerState
{
public:
	IAR60xPowerState();
	virtual ~IAR60xPowerState();

	virtual void PowerGetState(PowerState & state) = 0;
};

