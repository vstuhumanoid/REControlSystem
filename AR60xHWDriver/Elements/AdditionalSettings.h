#pragma once

#include <string>

/*
* Дополнительные настройки робота
* такие как (хост, порт, частота обновления...)
*/
class AdditionalSettings
{
public:
	std::string hostAddress; // IP адрес ПК робота
	int hostPort; // Порт ПК робота
	int delayForUpdate; // Задержка на обновление информации

	AdditionalSettings();
	~AdditionalSettings();
};

