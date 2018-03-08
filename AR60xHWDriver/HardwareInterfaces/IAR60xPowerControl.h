#pragma once

#include "../Elements/PowerSettings.h"

class IAR60xPowerControl
{
public:
	virtual void PowerSetSettings(PowerSettings settings) = 0;
    virtual void PowerSetState(PowerSettings::Powers power, bool onOffState) = 0;
};

