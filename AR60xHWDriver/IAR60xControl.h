#pragma once

#include "HardwareInterfaces\IAR60xJointControl.h"
#include "HardwareInterfaces\IAR60xJointState.h"
#include "HardwareInterfaces\IAR60xPowerControl.h"
#include "HardwareInterfaces\IAR60xPowerState.h"
#include "HardwareInterfaces\IAR60xSensorState.h"
#include "Elements\AdditionalSettings.h"

class IAR60xControl : 
	IAR60xJointControl, 
	IAR60xJointState, 
	IAR60xPowerControl, 
	IAR60xPowerState, 
	IAR60xSensorState
{
public:
	virtual void setSettings(AdditionalSettings settings) = 0;
	virtual void getSettings(AdditionalSettings &settings) = 0;
};

