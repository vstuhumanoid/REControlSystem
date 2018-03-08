#pragma once

#include "../Elements/PowerState.h"
#include "../Elements/PowerSettings.h"

class IAR60xPowerState
{
public:
    virtual bool PowerGetOnOff(PowerSettings::Powers power) = 0;
    virtual PowerState::PowerSupplyState PowerGetSupplyState(PowerSettings::Powers power) = 0;
};

