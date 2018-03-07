#include "JSONSerializer.h"

JSONSerializer::JSONSerializer()
{

}

void JSONSerializer::setDesc(AR60xDescription *desc)
{
    this->desc = desc;
}

bool JSONSerializer::serialize(std::string fileName)
{
    QJsonDocument document;
    json j;
    for(auto it = desc->joints.begin(); it != desc->joints.end(); ++it)
    {
        int number = (*it).second.jointNumber;
        std::string jointNumber = std::to_string(number);
        j["jointsInformation"][jointNumber.c_str()]["number"] = (*it).second.jointNumber;
        j["jointsInformation"][jointNumber.c_str()]["name"] = (*it).second.jointName;
        j["jointsInformation"][jointNumber.c_str()]["channel"] = (*it).second.channel;
        j["jointsInformation"][jointNumber.c_str()]["gates"]["propGate"] = (*it).second.gates.propGate;
        j["jointsInformation"][jointNumber.c_str()]["gates"]["intGate"] = (*it).second.gates.intGate;
        j["jointsInformation"][jointNumber.c_str()]["gates"]["diffGate"] = (*it).second.gates.diffGate;
        j["jointsInformation"][jointNumber.c_str()]["limits"]["lowerLimit"] = (*it).second.limits.lowerLimit;
        j["jointsInformation"][jointNumber.c_str()]["limits"]["upperLimit"] = (*it).second.limits.upperLimit;
        j["jointsInformation"][jointNumber.c_str()]["offset"] = (*it).second.offset;
        j["jointsInformation"][jointNumber.c_str()]["isReverce"] = (*it).second.isReverce;
        j["jointsInformation"][jointNumber.c_str()]["isEnable"] = (*it).second.isEnable;
    }

    for(auto it = desc->sensors.begin(); it != desc->sensors.end(); ++it)
    {
        int number = (*it).second.sensorNumber;
        std::string sensorNumber = std::to_string(number);
        j["sensorsInformation"][sensorNumber.c_str()]["number"] = (*it).second.sensorNumber;
        j["sensorsInformation"][sensorNumber.c_str()]["name"] = (*it).second.sensorName;
        j["sensorsInformation"][sensorNumber.c_str()]["channel"] = (*it).second.channel;
        j["sensorsInformation"][sensorNumber.c_str()]["group"] = (*it).second.group;
    }

    std::ofstream o(fileName);
    o << std::setw(4) << j << std::endl;
}

bool JSONSerializer::deserialize(std::string fileName)
{

}
