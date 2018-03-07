#pragma once

#include <string>

/*
* Настройки узла (мотора)
*/
class JointSettings
{
public:
    int number; // номер узла (мотора)
	int channel; // канал (в роботе)
	int offset; // смещение угла (градусы * 100)

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

	PIDGates gates; // пиды
	bool isEnable; // используется
	bool isReverce; // реверс

	std::string name; // название узла

	JointSettings();
	~JointSettings();
};

