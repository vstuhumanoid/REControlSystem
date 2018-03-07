#pragma once

#include "../Elements/JointSettings.h"
#include "../Elements/JointState.h"
#include "../Elements/PowerState.h"

using SupplyState = PowerState::PowerSupplyState;
using JointLimits = JointSettings::JointLimits;

class IAR60xJointState
{
public:
	virtual void JointsGetPositions(int joints[], int positions[]) = 0;
    virtual void JointGetSettings(int joint, JointSettings & settings) = 0;

    virtual int JointGetPosition(int joint) = 0;
	virtual JointState JointGetState(int joint) = 0;
    virtual bool JointGetReverce(int joint) = 0;
    virtual SupplyState JointGetSupplyState(int joint) = 0;
    virtual JointLimits JointGetLimits(int joint) = 0;
    virtual void JointGetEnable(int joint) = 0;
};

