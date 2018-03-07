#pragma once

#include "../Elements/JointSettings.h"
#include "../Elements/JointState.h"

using JointLimits = JointSettings::JointLimits;
using PIDGates = JointSettings::PIDGates;

class IAR60xJointControl
{
public:

	virtual void JointsSetPositions(int joints[], int positions[]) = 0;
	virtual void JointSetSettings(int joint, JointSettings settings) = 0;

    virtual void JointSetPosition(int joint, int position) = 0;
    virtual void JointSetOffset(int joint, int offset) = 0;
    virtual void JointSetReverce(int joint, bool isReverce) = 0;
    virtual void JointSetGates(int joint, PIDGates gates) = 0;
    virtual void JointSetLimits(int joint, JointLimits limits) = 0;
    virtual void JointSetEnable(int joint, bool isEnable) = 0;
    virtual void JointSetState(int joint, JointState state) = 0;
};

