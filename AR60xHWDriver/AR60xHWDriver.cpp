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
        QJsonObject jointInformation;
        jointInformation["number"] = (*it).second.jointNumber;
        jointInformation["name"] = QString::fromStdString( (*it).second.jointName );
        jointInformation["channel"] = (*it).second.channel;

        QJsonObject jointGates;
        jointGates["propGate"] = (*it).second.gains.proportional;
        jointGates["intGate"] = (*it).second.gains.integral;
        jointGates["diffGate"] = (*it).second.gains.derivative;
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
    std::map <int, JointInformation> jointsMap;

    for(auto jointInformationRef : joints)
    {
        QJsonObject jointInformation = jointInformationRef.toObject();

        JointInformation joint;
        joint.jointNumber = jointInformation["number"].toInt();
        joint.jointName = jointInformation["name"].toString().toStdString();
        joint.channel = jointInformation["channel"].toInt();

        QJsonObject jointGates = jointInformation["gates"].toObject();

        joint.gains.proportional = jointGates["propGate"].toInt();
        joint.gains.integral = jointGates["intGate"].toInt();
        joint.gains.derivative = jointGates["diffGate"].toInt();

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

AR60xHWDriver::AR60xHWDriver()
{
    desc = new AR60xDescription();
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

void AR60xHWDriver::JointsSetPositions(int joints[], int positions[])
{

}

void AR60xHWDriver::JointSetSettings(int joint, JointSettings settings)
{

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

void AR60xHWDriver::JointSetPIDGains(int joint, JointSettings::PIDGains gains)
{
    sendpacket->jointSetPGain(joint, gains.proportional);
    sendpacket->jointSetIGain(joint, gains.integral);
    sendpacket->jointSetDGain(joint, gains.derivative);
}

void AR60xHWDriver::JointSetLimits(int joint, JointSettings::JointLimits limits)
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

void AR60xHWDriver::JointsGetPositions(int joints[], int positions[])
{

}

void AR60xHWDriver::JointGetSettings(int joint, JointSettings &settings)
{

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
JointSettings::JointLimits AR60xHWDriver::JointGetLimits(int joint)
{
    //return desc->joints.at(joint).limits;
}

bool AR60xHWDriver::JointGetEnable(int joint)
{
    return desc->joints.at(joint).isEnable;
}

JointSettings::PIDGains AR60xHWDriver::JointGetPIDGains(int joint)
{
    //return desc->joints.at(joint).gains;
}

void AR60xHWDriver::PowerSetSettings(PowerSettings settings)
{

}

void AR60xHWDriver::PowerSetState(PowerSettings::Powers power, bool onOffState)
{
    //TODO: заменить на PowerSetting::Powers в пакете
    if(onOffState)
        sendpacket->PowerSetOn(power);
    else
        sendpacket->PowerSetOff(power);
}

bool AR60xHWDriver::PowerGetOnOff(PowerSettings::Powers power)
{
    //TODO: нет метода в recvpacket
}

PowerState::PowerSupplyState AR60xHWDriver::PowerGetSupplyState(PowerSettings::Powers power)
{
    PowerState::PowerSupplyState state;
    state.Voltage = recvPacket->powerGetVoltage(power);
    state.Current = recvPacket->powerGetCurrent(power);
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

bool AR60xHWDriver::saveConfig(std::string fileName)
{
    JointInformation joint;
    joint.channel = 2;
    joint.isEnable = false;
    joint.isReverce = false;
    joint.jointName = "joint 1";
    joint.offset = 34455;
    joint.jointNumber = 1;

    JointInformation::PIDGains gates;
    gates.derivative = 5;
    gates.integral = 6;
    gates.proportional = 1200;

    joint.gains = gates;

    JointInformation::JointLimits limits;
    limits.lowerLimit = -1300;
    limits.upperLimit = 1500;

    joint.limits = limits;

    desc->joints[1] = joint;

    JointInformation joint2;

    joint2.jointNumber = 2;

    joint2.channel = 2;
    joint2.isEnable = false;
    joint2.isReverce = false;
    joint2.jointName = "joint 2";
    joint2.offset = 34455;

    gates.derivative = 5;
    gates.integral = 6;
    gates.proportional = 1200;

    joint2.gains = gates;

    limits.lowerLimit = -1300;
    limits.upperLimit = 1500;

    joint2.limits = limits;

    desc->joints[2] = joint2;

    SensorInformation sensor1;
    sensor1.sensorNumber = 1;
    sensor1.sensorName = "Датчик скорости";
    sensor1.group = SensorInformation::IMUSensors;
    sensor1.channel = 1;

    SensorInformation sensor2;
    sensor2.sensorNumber = 2;
    sensor2.sensorName = "Датчик давления";
    sensor2.group = SensorInformation::FootPressureSensors;
    sensor2.channel = 2;

    desc->sensors[1] = sensor1;
    desc->sensors[2] = sensor2;

    return serialize(fileName);
}

bool AR60xHWDriver::generateConfig(std::string fileName)
{
    JointInformation joint;

    joint.jointNumber = 1;
    joint.channel = 1;
    joint.jointName = "Стопа Y (R)";
    joint.offset = -114;
    joint.gains.proportional = 900;
    joint.gains.integral = 2;
    joint.gains.derivative = 1;
    joint.limits.lowerLimit = -1500;
    joint.limits.upperLimit = 1500;
    joint.isReverce = false;
    joint.isEnable = true;

    desc->joints[joint.jointNumber] = joint;

    joint.jointNumber = 2;
    joint.channel = 2;
    joint.jointName = "Стопа X (R)";
    joint.offset = -5361;
    joint.gains.proportional = 900;
    joint.gains.integral = 2;
    joint.gains.derivative = 1;
    joint.limits.lowerLimit = -4000;
    joint.limits.upperLimit = 8000;
    joint.isReverce = false;
    joint.isEnable = true;

    desc->joints[joint.jointNumber] = joint;

    joint.jointNumber = 3;
    joint.channel = 3;
    joint.jointName = "Колено (R)";
    joint.offset = -7804;
    joint.gains.proportional = 900;
    joint.gains.integral = 2;
    joint.gains.derivative = 1;
    joint.limits.lowerLimit = -10000;
    joint.limits.upperLimit = 700;
    joint.isReverce = false;
    joint.isEnable = true;

    desc->joints[joint.jointNumber] = joint;

    joint.jointNumber = 4;
    joint.channel = 4;
    joint.jointName = "Бедро X (R)";
    joint.offset = 4851;
    joint.gains.proportional = 900;
    joint.gains.integral = 2;
    joint.gains.derivative = 1;
    joint.limits.lowerLimit = -1000;
    joint.limits.upperLimit = 7500;
    joint.isReverce = true;
    joint.isEnable = true;

    desc->joints[joint.jointNumber] = joint;

    joint.jointNumber = 5;
    joint.channel = 5;
    joint.jointName = "Бедро Y (R)";
    joint.offset = 193;
    joint.gains.proportional = 900;
    joint.gains.integral = 2;
    joint.gains.derivative = 1;
    joint.limits.lowerLimit = -1400;
    joint.limits.upperLimit = 1500;
    joint.isReverce = true;
    joint.isEnable = true;

    desc->joints[joint.jointNumber] = joint;

    joint.jointNumber = 6;
    joint.channel = 6;
    joint.jointName = "Бедро вращение (R)";
    joint.offset = 8208;
    joint.gains.proportional = 900;
    joint.gains.integral = 2;
    joint.gains.derivative = 1;
    joint.limits.lowerLimit = -1000;
    joint.limits.upperLimit = 1000;
    joint.isReverce = true;
    joint.isEnable = true;

    desc->joints[joint.jointNumber] = joint;

    joint.jointNumber = 7;
    joint.channel = 7;
    joint.jointName = "Стопа Y (L)";
    joint.offset = 6389;
    joint.gains.proportional = 900;
    joint.gains.integral = 2;
    joint.gains.derivative = 1;
    joint.limits.lowerLimit = -1500;
    joint.limits.upperLimit = 1500;
    joint.isReverce = true;
    joint.isEnable = true;

    desc->joints[joint.jointNumber] = joint;

    joint.jointNumber = 8;
    joint.channel = 8;
    joint.jointName = "Стопа X (L)";
    joint.offset = -870;
    joint.gains.proportional = 900;
    joint.gains.integral = 2;
    joint.gains.derivative = 1;
    joint.limits.lowerLimit = -4000;
    joint.limits.upperLimit = 8000;
    joint.isReverce = true;
    joint.isEnable = true;

    desc->joints[joint.jointNumber] = joint;

    joint.jointNumber = 9;
    joint.channel = 9;
    joint.jointName = "Колено (L)";
    joint.offset = -4965;
    joint.gains.proportional = 900;
    joint.gains.integral = 2;
    joint.gains.derivative = 1;
    joint.limits.lowerLimit = -10000;
    joint.limits.upperLimit = 700;
    joint.isReverce = true;
    joint.isEnable = true;

    desc->joints[joint.jointNumber] = joint;

    joint.jointNumber = 10;
    joint.channel = 10;
    joint.jointName = "Бедро X (L)";
    joint.offset = -4429;
    joint.gains.proportional = 900;
    joint.gains.integral = 2;
    joint.gains.derivative = 1;
    joint.limits.lowerLimit = -1000;
    joint.limits.upperLimit = 7500;
    joint.isReverce = false;
    joint.isEnable = true;

    desc->joints[joint.jointNumber] = joint;

    joint.jointNumber = 11;
    joint.channel = 11;
    joint.jointName = "Бедро Y (L)";
    joint.offset = 4218;
    joint.gains.proportional = 900;
    joint.gains.integral = 2;
    joint.gains.derivative = 1;
    joint.limits.lowerLimit = -1400;
    joint.limits.upperLimit = 1500;
    joint.isReverce = false;
    joint.isEnable = true;

    desc->joints[joint.jointNumber] = joint;

    joint.jointNumber = 12;
    joint.channel = 12;
    joint.jointName = "Бедро вращение (L)";
    joint.offset = 7664;
    joint.gains.proportional = 900;
    joint.gains.integral = 2;
    joint.gains.derivative = 1;
    joint.limits.lowerLimit = -1000;
    joint.limits.upperLimit = 1000;
    joint.isReverce = false;
    joint.isEnable = true;

    desc->joints[joint.jointNumber] = joint;

    return serialize(fileName);
}
