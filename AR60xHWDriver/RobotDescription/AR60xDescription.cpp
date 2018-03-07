#include "AR60xDescription.h"

AR60xDescription::AR60xDescription()
{

}

std::map<int, SensorInformation> *AR60xDescription::getSensors()
{
    return &sensors;
}

std::map<int, JointInformation> *AR60xDescription::getJoints()
{
    return &joints;
}
