#pragma once

#include "HardwareInterfaces\IAR60xJointControl.h"
#include "HardwareInterfaces\IAR60xJointState.h"
#include "HardwareInterfaces\IAR60xPowerControl.h"
#include "HardwareInterfaces\IAR60xPowerState.h"
#include "HardwareInterfaces\IAR60xSensorState.h"
#include "Elements\AdditionalSettings.h"

class IAR60xDriver : 
	IAR60xJointControl, 
	IAR60xJointState, 
	IAR60xPowerControl, 
	IAR60xPowerState, 
	IAR60xSensorState
{
public:
	IAR60xDriver();
	virtual ~IAR60xDriver();

	virtual void setSettings(AdditionalSettings settings) = 0;
	virtual void getSettings(AdditionalSettings &settings) = 0;

};

