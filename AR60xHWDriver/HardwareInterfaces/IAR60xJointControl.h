#pragma once

#include "../Elements/JointSettings.h"
#include "../Elements/JointState.h"

class IAR60xJointControl
{
public:
	virtual void JointSetPosition(int joint, int position) = 0;
	virtual void JointsSetPositions(int joints[], int positions[]) = 0;
	virtual void JointSetSettings(int joint, JointSettings settings) = 0;
	virtual void JointSetState(JointState state) = 0;
};

