#pragma once
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

	JointState();
	~JointState();
};

