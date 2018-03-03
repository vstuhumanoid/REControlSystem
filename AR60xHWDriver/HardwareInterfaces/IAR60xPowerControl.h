#pragma once

#include "../Elements/PowerSettings.h"

class IAR60xPowerControl
{
public:
	virtual void PowerSetSettings(PowerSettings settings) = 0;
};

