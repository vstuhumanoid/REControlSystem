#pragma once

#include "../Elements/PowerSettings.h"

using Powers = PowerSettings::Powers;

class IAR60xPowerControl
{
public:
	virtual void PowerSetSettings(PowerSettings settings) = 0;
    virtual void PowerSetState(Powers power, bool onOffState) = 0;
};

