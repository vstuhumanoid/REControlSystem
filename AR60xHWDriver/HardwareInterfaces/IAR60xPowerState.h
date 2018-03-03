#pragma once

#include "../Elements/PowerState.h"

class IAR60xPowerState
{
public:
	virtual void PowerGetState(PowerState & state) = 0;
};

