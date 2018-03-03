#pragma once

#include "PIDGates.h"
#include <string>

/*
* Настройки узла (мотора)
*/
class JointSettings
{
public:
	int Number; // номер узла (мотора)
	int channel; // канал (в роботе)
	int offset; // смещение угла (градусы * 100)
	int minAngle; // минимальный угол
	int maxAngle; // максимальный угол
	PIDGates gates; // пиды
	bool isEnable; // используется
	bool isReverce; // реверс

	std::string name; // название узла

	JointSettings();
	~JointSettings();
};

