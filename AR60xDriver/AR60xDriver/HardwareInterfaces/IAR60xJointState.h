#pragma once

#include "../Elements/JointSettings.h"
#include "../Elements/JointState.h"

class IAR60xJointState
{
public:
	virtual int JointGetPosition(int joint) = 0;
	virtual void JointsGetPositions(int joints[], int positions[]) = 0;
	virtual void JointGetSettings(int joint, JointSettings & settings) = 0;
	virtual JointState JointGetState(int joint) = 0;
};

