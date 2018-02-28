#pragma once

#include "../Elements/JointSettings.h"
class IAR60xJointControl
{
public:
	IAR60xJointControl();
	virtual ~IAR60xJointControl();

	//TODO: �������� ����� ���������� ������� �� ������
	virtual void JointSetPosition(int joint, int position) = 0;
	virtual void JointsSetPositions(int joints[], int positions[]) = 0;
	virtual void JointSetSettings(int joint, JointSettings settings) = 0;
};

