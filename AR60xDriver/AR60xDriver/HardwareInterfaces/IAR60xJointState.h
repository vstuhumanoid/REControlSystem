#pragma once

#include "../Elements/JointSettings.h"

class IAR60xJointState
{
public:
	IAR60xJointState();
	virtual ~IAR60xJointState();

	virtual int JointGetPosition(int joint) = 0;
	virtual void JointsGetPositions(int joints[], int positions[]) = 0;
	virtual void JointGetSettings(int joint, JointSettings & settings) = 0;
};

