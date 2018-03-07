#ifndef AR60XDESCRIPTION_H
#define AR60XDESCRIPTION_H

#include <map>

#include "SensorInformation.h"
#include "JointInformation.h"


class AR60xDescription
{
public:
    std::map<int, SensorInformation> sensors;
    std::map<int, JointInformation> joints;
    AR60xDescription();
    std::map<int, SensorInformation> *getSensors();
    std::map<int, JointInformation> *getJoints();
};

#endif // AR60XDESCRIPTION_H
