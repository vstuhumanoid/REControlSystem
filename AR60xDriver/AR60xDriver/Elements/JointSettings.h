#pragma once

#include "PIDGates.h"
#include <string>

/*
* ��������� ���� (������)
*/
class JointSettings
{
public:
	int Number; // ����� ���� (������)
	int channel; // ����� (� ������)
	int offset; // �������� ���� (������� * 100)
	int minAngle; // ����������� ����
	int maxAngle; // ������������ ����
	PIDGates gates; // ����
	bool isEnable; // ������������
	bool isReverce; // ������

	std::string name; // �������� ����

	JointSettings();
	~JointSettings();
};

