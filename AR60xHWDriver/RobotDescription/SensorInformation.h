#ifndef SENSORINFORMATION_H
#define SENSORINFORMATION_H

#include <string>

class SensorInformation
{
public:
    int sensorNumber;       // Номер датчика
    int channel;            // Канал в пакете управления
    std::string sensorName; // Имя датчика

    enum SensorGroups       // Группы датчиков
    {
        IMUSensors,
        FootPressureSensors
    };

    SensorGroups group;     // Группа датчика

    SensorInformation();
};

#endif // SENSORINFORMATION_H
