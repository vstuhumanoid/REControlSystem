#include "XMLSerializer.h"

XMLSerializer::XMLSerializer()
{

}

bool XMLSerializer::deserialize(std::string fileName)
{
    XMLDocument document;
    XMLError eResult =  document.LoadFile(fileName.c_str());
    if(eResult != XML_SUCCESS)
    {
        return false;
    }

    XMLElement *root = document.FirstChildElement();

    XMLElement *joints = 0;
    XMLElement *sensors = 0;
    XMLElement *jointData = 0;
    XMLElement *sensorData = 0;

    joints = root->FirstChildElement("joints");
    jointData = joints->FirstChildElement("joint");

    std::map <int, JointData> jointsMap;

    while(jointData != nullptr)
    {
        //int number;
        //eResult = jointData->QueryAttribute("number", &number);
        //if(eResult != XML_SUCCESS) return;

        JointData joint;
        jointData->QueryAttribute("number", &joint.number);
        jointData->Attribute("name", joint.name.c_str());
        jointData->QueryAttribute("channel", &joint.channel);

        XMLElement *jointGains = jointData->FirstChildElement("gains");

        jointGains->QueryAttribute("proportional", &joint.gains.proportional);
        jointGains->QueryAttribute("integral", &joint.gains.integral);
        jointGains->QueryAttribute("derivative", &joint.gains.derivative);

        XMLElement *jointLimits = jointData->FirstChildElement("limits");

        jointLimits->QueryAttribute("lowerLimit", &joint.limits.lowerLimit);
        jointLimits->QueryAttribute("upperLimit", &joint.limits.upperLimit);

        jointData->QueryAttribute("offset", &joint.offset);
        jointData->QueryAttribute("isReverce", &joint.isReverce);
        jointData->QueryAttribute("isEnable", &joint.isEnable);

        jointsMap[joint.number] = joint;

        jointData = jointData->NextSiblingElement("joint");
    }

    sensors = root->FirstChildElement("sensors");
    sensorData = sensors->FirstChildElement("sensor");

    std::map <int, SensorData> sensorsMap;

    while(sensorData != nullptr)
    {
        SensorData sensor;
        sensorData->QueryAttribute("number", &sensor.number);
        sensorData->Attribute("name", sensor.name.c_str());
        sensorData->QueryAttribute("channel", &sensor.channel);

        sensorsMap[sensor.number] = sensor;

        sensorData = sensorData->NextSiblingElement("sensor");
    }

    return true;
}

bool XMLSerializer::serialize(std::string fileName, AR60xDescription * desc)
{
    XMLDocument document;
    XMLNode * root = document.NewElement("config");

    XMLElement *joints = document.NewElement("joints");
    XMLElement *sensors = document.NewElement("sensors");

    for(auto it = desc->joints.begin(); it != desc->joints.end(); ++it)
    {
        JointData joint = (*it).second;

        XMLElement *jointData = document.NewElement("joint");
        jointData->SetAttribute("number", joint.number);
        jointData->SetAttribute("name", joint.name.c_str() );
        jointData->SetAttribute("channel", joint.channel);

        XMLElement *jointGains = document.NewElement("gains");
        jointGains->SetAttribute("proportional", joint.gains.proportional);
        jointGains->SetAttribute("integral", joint.gains.integral);
        jointGains->SetAttribute("derivative", joint.gains.derivative);
        jointData->InsertEndChild(jointGains);

        XMLElement *jointLimits = document.NewElement("limits");
        jointLimits->SetAttribute("lowerLimit", joint.limits.lowerLimit);
        jointLimits->SetAttribute("upperLimit", joint.limits.upperLimit);
        jointData->InsertEndChild(jointLimits);

        jointData->SetAttribute("offset", joint.offset);
        jointData->SetAttribute("isReverce", joint.isReverce);
        jointData->SetAttribute("isEnable", joint.isEnable);

        joints->InsertEndChild(jointData);
    }

    root->InsertEndChild(joints);
    document.InsertEndChild(root);

    XMLError eResult = document.SaveFile(fileName.c_str());

    if(eResult != XML_SUCCESS)
    {
        return false;
    }

    return true;
}
