#include "AR60xHWDriver.h"

bool AR60xHWDriver::serialize(std::string fileName)
{
    QJsonObject root;

    QJsonObject connectionInfo;
    connectionInfo["host"] = QString::fromStdString( connectionData.host );
    connectionInfo["recvPort"] = connectionData.recvPort;
    connectionInfo["sendPort"] = connectionData.sendPort;
    connectionInfo["sendDelay"] = connectionData.sendDelay;
    root["connection"] = connectionInfo;

    QJsonArray joints;

    for(auto it = desc->joints.begin(); it != desc->joints.end(); ++it)
    {
        QJsonObject jointData;
        jointData["number"] = (*it).second.number;
        jointData["name"] = QString::fromStdString( (*it).second.name );
        jointData["channel"] = (*it).second.channel;

        QJsonObject jointGates;
        jointGates["propGate"] = (*it).second.gains.proportional;
        jointGates["intGate"] = (*it).second.gains.integral;
        jointGates["diffGate"] = (*it).second.gains.derivative;
        jointData["gates"] = jointGates;

        QJsonObject jointLimits;
        jointLimits["lowerLimit"] = (*it).second.limits.lowerLimit;
        jointLimits["upperLimit"] = (*it).second.limits.upperLimit;
        jointData["limits"] = jointLimits;

        jointData["offset"] = (*it).second.offset;
        jointData["isReverce"] = (*it).second.isReverce;
        jointData["isEnable"] = (*it).second.isEnable;

        joints.append(jointData);
    }

    root["joints"] = joints;

    QJsonArray sensors;

    for(auto it = desc->sensors.begin(); it != desc->sensors.end(); ++it)
    {
        QJsonObject sensorData;
        sensorData["number"] = (*it).second.number;
        sensorData["name"] = QString::fromStdString( (*it).second.name );
        sensorData["channel"] = (*it).second.channel;

        sensors.append(sensorData);
    }

    root["sensors"] = sensors;

    QFile file;
    file.setFileName(QString::fromStdString( fileName ));
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.write(QJsonDocument(root).toJson(QJsonDocument::Indented));
    file.close();

    return true;
}

bool AR60xHWDriver::deserialize(std::string fileName)
{
    QFile file;
    file.setFileName(QString::fromStdString( fileName ));
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument document;

    document = QJsonDocument::fromJson(jsonData);
    if (!document.isObject())
    {
        qDebug() << "Document is not an object";
        return false;
    }

    QJsonObject root = document.object();

    QJsonObject connectionInfo = root["connection"].toObject();
    connectionData.host = connectionInfo["host"].toString().toStdString();
    connectionData.recvPort = connectionInfo["recvPort"].toInt();
    connectionData.sendPort = connectionInfo["sendPort"].toInt();
    connectionData.sendDelay = connectionInfo["sendDelay"].toInt();

    QJsonArray joints = root["joints"].toArray();
    std::map <int, JointData> jointsMap;

    for(auto jointDataRef : joints)
    {
        QJsonObject jointData = jointDataRef.toObject();

        JointData joint;
        joint.number = jointData["number"].toInt();
        joint.name = jointData["name"].toString().toStdString();
        joint.channel = jointData["channel"].toInt();

        QJsonObject jointGates = jointData["gates"].toObject();

        joint.gains.proportional = jointGates["propGate"].toInt();
        joint.gains.integral = jointGates["intGate"].toInt();
        joint.gains.derivative = jointGates["diffGate"].toInt();

        QJsonObject jointLimits = jointData["limits"].toObject();
        joint.limits.lowerLimit = jointLimits["lowerLimit"].toInt();
        joint.limits.upperLimit = jointLimits["upperLimit"].toInt();

        joint.offset = jointData["offset"].toInt();
        joint.isReverce = jointData["isReverce"].toBool();
        joint.isEnable = jointData["isEnable"].toBool();

        jointsMap[joint.number] = joint;
    }

    QJsonArray sensors = root["sensors"].toArray();
    std::map <int, SensorData> sensorsMap;

    for(auto sensorDataRef : sensors)
    {
        QJsonObject sensorData = sensorDataRef.toObject();
        SensorData sensor;
        sensor.number = sensorData["number"].toInt();
        sensor.name = sensorData["name"].toString().toStdString();
        sensor.channel = sensorData["channel"].toInt();

        sensorsMap[sensor.number] = sensor;
    }

    desc->joints = jointsMap;
    desc->sensors = sensorsMap;

    return true;
}

AR60xHWDriver::AR60xHWDriver(ILogger *logger)
{
    this->_logger = logger;
    desc = new AR60xDescription();
    _logger->addMessage("AR600xHWDriver created", ILogger::Info);
}

bool AR60xHWDriver::loadConfig(std::string fileName)
{
    return deserialize(fileName);
}

void AR60xHWDriver::initPackets()
{
    sendpacket = new AR60xSendPacket(desc);
    recvPacket = new AR60xRecvPacket(desc);

    connection = new UDPConnection();

    connection->setRecvPacket(recvPacket);
    connection->setSendPacket(sendpacket);

    connection->initPackets();
}

void AR60xHWDriver::robotConnect()
{
    connection->connectToHost(connectionData.host,
                              connectionData.sendPort,
                              connectionData.recvPort,
                              connectionData.sendDelay);
}

void AR60xHWDriver::robotDisconnect()
{
    connection->breakConnection();
    connection->wait();
}

void AR60xHWDriver::JointSetSettings(int joint, JointData settings)
{
    desc->joints.at(joint) = settings;
}

void AR60xHWDriver::JointSetPosition(int joint, int position)
{
    sendpacket->jointSetPosition(joint, position);
}

void AR60xHWDriver::JointSetOffset(int joint, int offset)
{
    desc->joints.at(joint).offset = offset;
    sendpacket->jointSetOffset(joint, offset);
}

void AR60xHWDriver::JointSetReverce(int joint, bool isReverce)
{
    desc->joints.at(joint).isReverce = isReverce;
}

void AR60xHWDriver::JointSetPIDGains(int joint, JointData::PIDGains gains)
{
    sendpacket->jointSetPGain(joint, gains.proportional);
    sendpacket->jointSetIGain(joint, gains.integral);
    sendpacket->jointSetDGain(joint, gains.derivative);
}

void AR60xHWDriver::JointSetLimits(int joint, JointData::JointLimits limits)
{
    sendpacket->jointSetLowerLimit(joint, limits.lowerLimit);
    sendpacket->jointSetUpperLimit(joint, limits.upperLimit);
}

void AR60xHWDriver::JointSetEnable(int joint, bool isEnable)
{
    desc->joints.at(joint).isEnable = isEnable;
}

void AR60xHWDriver::JointSetState(int joint, JointState::JointStates state)
{
    sendpacket->jointSetState(joint, state);
}

JointData AR60xHWDriver::JointGetSettings(int joint)
{
    return desc->joints.at(joint);
}

int AR60xHWDriver::JointGetPosition(int joint)
{
    return recvPacket->jointGetPosition(joint);
}

//TODO: проверить!!!!
JointState AR60xHWDriver::JointGetState(int joint)
{
    //return recvPacket->jointGetState(joint);
}

bool AR60xHWDriver::JointGetReverce(int joint)
{
    return desc->joints.at(joint).isReverce;
}

PowerState::PowerSupplyState AR60xHWDriver::JointGetSupplyState(int joint)
{
    PowerState::PowerSupplyState state;
    state.Voltage = recvPacket->jointGetVoltage(joint);
    state.Current = recvPacket->jointGetCurrent(joint);
    return state;
}

//TODO: Удалить JointSettings перенсти вместо него JointInformation!!!!!
JointData::JointLimits AR60xHWDriver::JointGetLimits(int joint)
{
    return desc->joints.at(joint).limits;
}

bool AR60xHWDriver::JointGetEnable(int joint)
{
    return desc->joints.at(joint).isEnable;
}

JointData::PIDGains AR60xHWDriver::JointGetPIDGains(int joint)
{
    return desc->joints.at(joint).gains;
}

void AR60xHWDriver::PowerSetSettings(PowerData settings)
{

}

void AR60xHWDriver::SupplySetState(PowerData::PowerSupplies supply, bool onOffState)
{
    if(onOffState)
        sendpacket->supplySetOn(supply);
    else
        sendpacket->supplySetOff(supply);
}

bool AR60xHWDriver::PowerGetOnOff(PowerData::PowerSupplies supply)
{
    //TODO: нет метода в recvpacket
}

PowerState::PowerSupplyState AR60xHWDriver::PowerGetSupplyState(PowerData::PowerSupplies supply)
{
    PowerState::PowerSupplyState state;
    state.Voltage = recvPacket->supplyGetVoltage(supply);
    state.Current = recvPacket->supplyGetCurrent(supply);
    return state;
}

SensorState AR60xHWDriver::SensorGetState(int sensor)
{
    //return recvPacket->sensorGetValue(sensor);
}

AR60xDescription *AR60xHWDriver::getRobotDesc()
{
    return desc;
}

void AR60xHWDriver::ser(std::string fileName)
{
    XMLser = new XMLSerializer();
    XMLser->serialize(fileName, desc);
}

bool AR60xHWDriver::saveConfig(std::string fileName)
{
    JointData joint;
    joint.channel = 2;
    joint.isEnable = false;
    joint.isReverce = false;
    joint.name = "joint 1";
    joint.offset = 34455;
    joint.number = 1;

    JointData::PIDGains gates;
    gates.derivative = 5;
    gates.integral = 6;
    gates.proportional = 1200;

    joint.gains = gates;

    JointData::JointLimits limits;
    limits.lowerLimit = -1300;
    limits.upperLimit = 1500;

    joint.limits = limits;

    desc->joints[1] = joint;

    JointData joint2;

    joint2.number = 2;

    joint2.channel = 2;
    joint2.isEnable = false;
    joint2.isReverce = false;
    joint2.name = "joint 2";
    joint2.offset = 34455;

    gates.derivative = 5;
    gates.integral = 6;
    gates.proportional = 1200;

    joint2.gains = gates;

    limits.lowerLimit = -1300;
    limits.upperLimit = 1500;

    joint2.limits = limits;

    desc->joints[2] = joint2;

    SensorData sensor1;
    sensor1.number = 1;
    sensor1.name = "Датчик скорости";
    sensor1.channel = 1;

    SensorData sensor2;
    sensor2.number = 2;
    sensor2.name = "Датчик давления";
    sensor2.channel = 2;

    desc->sensors[1] = sensor1;
    desc->sensors[2] = sensor2;

    XMLser = new XMLSerializer();
    return XMLser->serialize(fileName, desc);
    //return serialize(fileName);
}
