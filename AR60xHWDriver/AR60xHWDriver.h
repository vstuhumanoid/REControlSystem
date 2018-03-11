#ifndef AR60XHWDRIVER_H
#define AR60XHWDRIVER_H

#include "RobotDescription/AR60xDescription.h"

#include "RobotPackets/AR60xRecvPacket.h"
#include "RobotPackets/AR60xSendPacket.h"

#include "HardwareInterfaces/IAR60xJointControl.h"
#include "HardwareInterfaces/IAR60xJointState.h"
#include "HardwareInterfaces/IAR60xPowerControl.h"
#include "HardwareInterfaces/IAR60xPowerState.h"
#include "HardwareInterfaces/IAR60xSensorState.h"

#include "UDPConnection.h"

#include <string>
#include <fstream>
#include <sstream>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QFile>
#include <QJsonArray>

class AR60xHWDriver :
        IAR60xJointControl,
        IAR60xJointState,
        IAR60xPowerControl,
        IAR60xPowerState,
        IAR60xSensorState
{
private:
    AR60xDescription * desc;
    bool serialize(std::string fileName);
    bool deserialize(std::string fileName);

    UDPConnection *connection;
    AR60xRecvPacket *recvPacket;
    AR60xSendPacket *sendpacket;

    struct ConnectionSettings
    {
        std::string host;
        int sendPort;
        int recvPort;
        int sendDelay;
    };

    ConnectionSettings connectionData;
public:
    AR60xHWDriver();
    bool saveConfig(std::string fileName);
    bool generateConfig(std::string fileName);
    bool loadConfig(std::string fileName);
    void initPackets();

    // interfaces
    void robotConnect();
    void robotDisconnect();

    void JointsSetPositions(int joints[], int positions[]) override;
    void JointSetSettings(int joint, JointSettings settings)override;

    void JointSetPosition(int joint, int position)override;
    void JointSetOffset(int joint, int offset)override;
    void JointSetReverce(int joint, bool isReverce)override;
    void JointSetPIDGains(int joint, JointSettings::PIDGains gains)override;
    void JointSetLimits(int joint, JointSettings::JointLimits limits)override;
    void JointSetEnable(int joint, bool isEnable)override;
    void JointSetState(int joint, JointState::JointStates state)override;

    void JointsGetPositions(int joints[], int positions[])override;
    void JointGetSettings(int joint, JointSettings & settings)override;

    int JointGetPosition(int joint)override;
    JointState JointGetState(int joint)override;
    bool JointGetReverce(int joint)override;
    PowerState::PowerSupplyState JointGetSupplyState(int joint)override;
    JointSettings::JointLimits JointGetLimits(int joint)override;
    bool JointGetEnable(int joint)override;
    JointSettings::PIDGains JointGetPIDGains(int joint)override;

    void PowerSetSettings(PowerSettings settings)override;
    void PowerSetState(PowerSettings::Powers power, bool onOffState)override;

    bool PowerGetOnOff(PowerSettings::Powers power)override;
    PowerState::PowerSupplyState PowerGetSupplyState(PowerSettings::Powers power)override;

    SensorState SensorGetState(int sensor)override;

    AR60xDescription *getRobotDesc();

};

#endif // AR60XHWDRIVER_H
