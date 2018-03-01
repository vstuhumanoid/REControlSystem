#pragma once

#include "../Elements/SensorState.h"

class IAR60xSensorState
{
public:
	virtual void SensorGetState(int sensor, SensorState & state) = 0;
};

