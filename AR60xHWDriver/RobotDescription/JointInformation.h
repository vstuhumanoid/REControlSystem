#ifndef JOINTINFORMATION_H
#define JOINTINFORMATION_H

#include <string>

class JointInformation
{
public:
    int jointNumber;        // Номер узла
    std::string jointName;  // Имя узла

    int channel;            // Номер канала в пакете управления

    struct PIDGains         // Структура регулятора
    {
        int proportional;
        int integral;
        int derivative;
    };

    PIDGains gains;         // Коэффициенты регулирования

    struct JointLimits      // Структура пределов
    {
        int lowerLimit;
        int upperLimit;
    };

    JointLimits limits;     // Пределы

    int offset;             // Смещение абсолютного положения
    bool isReverce;         // Реверсировать углы
    bool isEnable;          // Задействовать узел

    JointInformation();
};

#endif // JOINTINFORMATION_H
