#ifndef AR60XPACKETDEFINITION_H
#define AR60XPACKETDEFINITION_H

#include "../Elements/PowerSettings.h"

#include <iostream>
#include <map>

typedef unsigned char BYTE;

const uint16_t packetSize  = 1472;
const uint16_t countChannels = 71;

const uint16_t SensorYawAddress = 2;
const uint16_t SensorPitchAddress = 4;
const uint16_t SensorRollAddress = 6;

const uint16_t SensorUch0Address = 8;
const uint16_t SensorUch1Address = 10;
const uint16_t SensorUch2Address = 12;
const uint16_t SensorUch3Address = 14;

const uint16_t SensorTxAddress = 8;
const uint16_t SensorTyAddress = 10;
const uint16_t SensorFzAddress = 12;

static std::map<int ,int> sensorsMap =
{
    {1, SensorYawAddress},
    {2, SensorPitchAddress},
    {3, SensorRollAddress},
    {4, SensorTxAddress},
    {5, SensorTyAddress},
    {6, SensorFzAddress},
    {7, SensorUch0Address},
    {8, SensorUch1Address},
    {9, SensorUch2Address},
    {10, SensorUch3Address},
    {11, SensorUch0Address},
    {12, SensorUch1Address},
    {13, SensorUch2Address},
    {14, SensorUch3Address}
};

const uint16_t DeviceNumberAddress =  0;

const uint16_t JointStateAddress =     1;
const uint16_t JointPositionAddress =     2;
const uint16_t JointVoltageAddress =   4;
const uint16_t JointCurrentAddress =   6;
const uint16_t JointOffsetAddress  =    6;
const uint16_t JointPGainAddress =    8;
const uint16_t JointIGaneAddress =    10;
const uint16_t JointDGainAddress =    4;
const uint16_t JointLowerLimitAddress = 12;
const uint16_t JointUpperLimitAddress = 14;

const uint16_t PowerDataAddress = 1408;

const uint16_t Power6V1VoltageAddress =   0 * 2 + PowerDataAddress;
const uint16_t Power6V2VoltageAddress =   1 * 2 + PowerDataAddress;
const uint16_t Power8V1VoltageAddress =   2 * 2 + PowerDataAddress;
const uint16_t Power8V2VoltageAddress =   3 * 2 + PowerDataAddress;
const uint16_t Power12VoltageAddress =    4 * 2 + PowerDataAddress;
const uint16_t Power48VoltageAddress =    5 * 2 + PowerDataAddress;

const uint16_t Power6V1CurrentAddress =   0 * 2 + 12 + PowerDataAddress;
const uint16_t Power6V2CurrentAddress =   1 * 2 + 12 + PowerDataAddress;
const uint16_t Power8V1CurrentAddress =   2 * 2 + 12 + PowerDataAddress;
const uint16_t Power8V2CurrentAddress =   3 * 2 + 12 + PowerDataAddress;
const uint16_t Power12CurrentAddress =    4 * 2 + 12 + PowerDataAddress;
const uint16_t Power48CurrentAddress =    5 * 2 + 12 + PowerDataAddress;

struct PowerStateAddress
{
    int PowerVoltageAddress;
    int PowerCurrentAddress;
};

static std::map<int ,PowerStateAddress> powerStateMap =
{
    {PowerSettings::Power12V, {Power12VoltageAddress, Power12CurrentAddress}},
    {PowerSettings::Power6V1, {Power6V1VoltageAddress, Power6V1CurrentAddress}},
    {PowerSettings::Power6V2, {Power6V2VoltageAddress, Power6V2CurrentAddress}},
    {PowerSettings::Power8V1, {Power8V1VoltageAddress, Power8V1CurrentAddress}},
    {PowerSettings::Power8V2, {Power8V2VoltageAddress, Power8V2CurrentAddress}},
    {PowerSettings::Power48V, {Power48VoltageAddress, Power48CurrentAddress}}
};

#endif // AR60XPACKETDEFINITION_H
