#pragma once

#include "../Elements/JointSettings.h"
#include "../Elements/JointState.h"
#include "../Elements/PowerState.h"

class IAR60xJointState
{
public:
	virtual void JointsGetPositions(int joints[], int positions[]) = 0;
    virtual void JointGetSettings(int joint, JointSettings & settings) = 0;

    virtual int JointGetPosition(int joint) = 0;
	virtual JointState JointGetState(int joint) = 0;
    virtual bool JointGetReverce(int joint) = 0;
    virtual PowerState::PowerSupplyState JointGetSupplyState(int joint) = 0;
    virtual JointSettings::JointLimits JointGetLimits(int joint) = 0;
    virtual void JointGetEnable(int joint) = 0;
    virtual JointSettings::PIDGates JointGetGates(int joint) = 0;
};

