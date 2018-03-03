#pragma once

/*
* Настройки блока питания
*/
class PowerSettings
{
public:

	bool isPower12VOn; // Включен источник 12 Вольт
	bool isPower6V1On; // Включен источник 6 Вольт (1)
	bool isPower6V2On; // Включен источник 6 Вольт (2)
	bool isPower8V1On; // Включен источник 8 Вольт (1)
	bool isPower8V2On; // Включен источник 8 Вольт (2)
	bool isPower48VOn; // Включен источник 48 Вольт

	PowerSettings();
	~PowerSettings();
};

