#pragma once

#include <string>

/*
* ��������� ���� (������)
*/
class JointSettings
{
public:
    int number; // ����� ���� (������)
	int channel; // ����� (� ������)
	int offset; // �������� ���� (������� * 100)

    struct JointLimits
    {
        int lowerLimit;
        int upperLimit;
    };

    JointLimits limits;

    struct PIDGates
    {
        int PropGate;
        int IntGate;
        int DiffGate;
    };

	PIDGates gates; // ����
	bool isEnable; // ������������
	bool isReverce; // ������

	std::string name; // �������� ����

	JointSettings();
	~JointSettings();
};

