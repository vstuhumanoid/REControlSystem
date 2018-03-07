#pragma once

#include "../Elements/PowerSettings.h"

class IAR60xPowerControl
{
public:
	virtual void PowerSetSettings(PowerSettings settings) = 0;
    virtual void PowerSetState(int power, bool onOffState) = 0;
};

