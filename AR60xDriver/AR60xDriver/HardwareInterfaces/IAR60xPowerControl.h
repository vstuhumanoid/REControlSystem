#pragma once

#include "../Elements/PowerSettings.h"

class IAR60xPowerControl
{
public:
	IAR60xPowerControl();
	virtual ~IAR60xPowerControl();

	virtual void PowerSetSettings(PowerSettings settings) = 0;
};

