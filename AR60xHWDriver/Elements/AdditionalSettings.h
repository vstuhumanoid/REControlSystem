#pragma once

#include <string>

/*
* �������������� ��������� ������
* ����� ��� (����, ����, ������� ����������...)
*/
class AdditionalSettings
{
public:
	std::string hostAddress; // IP ����� �� ������
	int hostPort; // ���� �� ������
	int delayForUpdate; // �������� �� ���������� ����������

	AdditionalSettings();
	~AdditionalSettings();
};

