#pragma once

#include "../Elements/PowerState.h"
#include "../Elements/PowerSettings.h"

using Powers = PowerSettings::Powers;
using SupplyState = PowerState::PowerSupplyState;

class IAR60xPowerState
{
public:
	virtual void PowerGetState(PowerState & state) = 0;
    virtual bool PowerGetOnOff(Powers power) = 0;
    virtual SupplyState PowerGetSupplyState(Powers power) = 0;
};

