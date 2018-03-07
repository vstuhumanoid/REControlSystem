#pragma once

#include "../Elements/PowerState.h"

using SupplyState = PowerState::PowerSupplyState;

class IAR60xPowerState
{
public:
	virtual void PowerGetState(PowerState & state) = 0;
    virtual bool PowerGetOnOff(int power) = 0;
    virtual SupplyState PowerGetSupplyState(int power) = 0;
};

