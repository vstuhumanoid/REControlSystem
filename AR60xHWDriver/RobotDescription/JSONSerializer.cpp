#include "JSONSerializer.h"

#include <QFile>
#include <QJsonArray>

JSONSerializer::JSONSerializer()
{

}

void JSONSerializer::setDesc(AR60xDescription *desc)
{
    this->desc = desc;
}

bool JSONSerializer::serialize(std::string fileName)
{
    QJsonObject root;

    QJsonObject json;
    QJsonArray joints;

    for(auto it = desc->joints.begin(); it != desc->joints.end(); ++it)
    {
        QJsonObject jointInformation;
        jointInformation["number"] = (*it).second.jointNumber;
        jointInformation["name"] = QString::fromStdString( (*it).second.jointName );
        jointInformation["channel"] = (*it).second.channel;

        QJsonObject jointGates;
        jointGates["propGate"] = (*it).second.gates.propGate;
        jointGates["intGate"] = (*it).second.gates.intGate;
        jointGates["diffGate"] = (*it).second.gates.diffGate;
        jointInformation["gates"] = jointGates;

        QJsonObject jointLimits;
        jointLimits["lowerLimit"] = (*it).second.limits.lowerLimit;
        jointLimits["upperLimit"] = (*it).second.limits.upperLimit;
        jointInformation["limits"] = jointLimits;

        jointInformation["offset"] = (*it).second.offset;
        jointInformation["isReverce"] = (*it).second.isReverce;
        jointInformation["isEnable"] = (*it).second.isEnable;

        joints.append(jointInformation);
    }

    root["joints"] = joints;

    QJsonArray sensors;

    for(auto it = desc->sensors.begin(); it != desc->sensors.end(); ++it)
    {
        QJsonObject sensorInformation;
        sensorInformation["number"] = (*it).second.sensorNumber;
        sensorInformation["name"] = QString::fromStdString( (*it).second.sensorName );
        sensorInformation["channel"] = (*it).second.channel;
        sensorInformation["group"] = (*it).second.group;

        sensors.append(sensorInformation);
    }

    root["sensors"] = sensors;


    std::string jsonString =
            QJsonDocument(root).toJson(QJsonDocument::Indented).toStdString();

    std::ofstream outputStream(fileName);
    outputStream << jsonString << std::endl;
}

bool JSONSerializer::deserialize(std::string fileName)
{
    QString jsonString;
    QFile file;
    file.setFileName(QString::fromStdString( fileName ));
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    jsonString = file.readAll();
    file.close();

    QJsonParseError jerror;
    QJsonDocument document;

    document = QJsonDocument::fromJson(jsonString.toLocal8Bit(), &jerror);
    if(jerror.error != QJsonParseError::NoError)
        return false;

    QJsonObject root = document.object();

    QJsonArray joints = root["joints"].toArray();
    std::map <int, JointInformation> jointsMap;

    for(auto jointInformationRef : joints)
    {
        QJsonObject jointInformation = jointInformationRef.toObject();

        JointInformation joint;
        joint.jointNumber = jointInformation["number"].toInt();
        joint.jointName = jointInformation["name"].toString().toStdString();
        joint.channel = jointInformation["channel"].toInt();

        QJsonObject jointGates = jointInformation["gates"].toObject();

        joint.gates.propGate = jointGates["propGate"].toInt();
        joint.gates.intGate = jointGates["intGate"].toInt();
        joint.gates.diffGate = jointGates["diffGate"].toInt();

        QJsonObject jointLimits = jointInformation["limits"].toObject();
        joint.limits.lowerLimit = jointLimits["lowerLimit"].toInt();
        joint.limits.upperLimit = jointLimits["upperLimit"].toInt();

        joint.offset = jointInformation["offset"].toInt();
        joint.isReverce = jointInformation["isReverce"].toBool();
        joint.isEnable = jointInformation["isEnable"].toBool();

        jointsMap[joint.jointNumber] = joint;
    }

    QJsonArray sensors = root["sensors"].toArray();
    std::map <int, SensorInformation> sensorsMap;

    for(auto sensorInformationRef : sensors)
    {
        QJsonObject sensorInformation = sensorInformationRef.toObject();
        SensorInformation sensor;
        sensor.sensorNumber = sensorInformation["number"].toInt();
        sensor.sensorName = sensorInformation["name"].toString().toStdString();
        sensor.channel = sensorInformation["channel"].toInt();
        sensor.group = SensorInformation::SensorGroups( sensorInformation["group"].toInt() );

        sensorsMap[sensor.sensorNumber] = sensor;
    }

    desc->joints = jointsMap;
    desc->sensors = sensorsMap;

    return true;
}
