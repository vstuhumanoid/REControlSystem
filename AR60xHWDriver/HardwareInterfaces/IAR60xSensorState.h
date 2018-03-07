#pragma once

#include "../Elements/SensorState.h"

class IAR60xSensorState
{
public:
    virtual SensorState SensorGetState(int sensor) = 0;
};

