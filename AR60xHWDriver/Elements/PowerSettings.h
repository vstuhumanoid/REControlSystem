#pragma once

/*
* ��������� ����� �������
*/
class PowerSettings
{
public:

	bool isPower12VOn; // ������� �������� 12 �����
	bool isPower6V1On; // ������� �������� 6 ����� (1)
	bool isPower6V2On; // ������� �������� 6 ����� (2)
	bool isPower8V1On; // ������� �������� 8 ����� (1)
	bool isPower8V2On; // ������� �������� 8 ����� (2)
	bool isPower48VOn; // ������� �������� 48 �����

	PowerSettings();
	~PowerSettings();
};

