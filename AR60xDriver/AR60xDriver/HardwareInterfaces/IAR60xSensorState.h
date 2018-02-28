#pragma once

#include "../Elements/SensorState.h"

class IAR60xSensorState
{
public:
	IAR60xSensorState();
	virtual ~IAR60xSensorState();

	virtual void SensorGetState(int sensor, SensorState & state) = 0;
};

