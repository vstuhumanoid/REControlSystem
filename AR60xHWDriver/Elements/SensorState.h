#pragma once

#include <string>

/*
* Состояния датчиков робота
*/
class SensorState
{
public:

	float sensorValue; // Значение величины
	std::string name; // Имя датчика

	SensorState();
	~SensorState();
};

