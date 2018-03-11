#ifndef AR60XDESCRIPTION_H
#define AR60XDESCRIPTION_H

#include <map>

#include "../DataTypes/JointData.h"
#include "../DataTypes/SensorData.h"


class AR60xDescription
{
public:
    std::map<int, SensorData> sensors;
    std::map<int, JointData> joints;

    AR60xDescription();
    std::map<int, SensorData> *getSensors();
    std::map<int, JointData> *getJoints();
};

#endif // AR60XDESCRIPTION_H
