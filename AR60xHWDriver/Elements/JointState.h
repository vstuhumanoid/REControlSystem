#pragma once

#include "PowerState.h"

class JointState
{
public:

	// ��������� ����� (�������)
	enum JOINT_STATES
	{
		BRAKE, // ����� ���������, ����� �������������
		STOP, // ����� �������, ����� ���������������
		RELAX, // ����� ���������, ����� ���������������
		TRACE // ����� ����������� �����
	};

    JOINT_STATES state;
    PowerState::PowerSupplyState supplyState;

	JointState();
	~JointState();
};

