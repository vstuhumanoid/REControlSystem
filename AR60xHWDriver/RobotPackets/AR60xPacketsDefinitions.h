#ifndef AR60XPACKETDEFINITION_H
#define AR60XPACKETDEFINITION_H

#include <iostream>
#include <map>

typedef unsigned char BYTE;

const uint16_t packetSize  = 1472;
const uint16_t countChannels = 71;

const uint16_t SENSOR_YAW = 2;
const uint16_t SENSOR_PITCH = 4;
const uint16_t SENSOR_ROLL = 6;

const uint16_t SENSOR_UCH0 = 8;
const uint16_t SENSOR_UCH1 = 10;
const uint16_t SENSOR_UCH2 = 12;
const uint16_t SENSOR_UCH3 = 14;

const uint16_t SENSOR_TX = 8;
const uint16_t SENSOR_TY = 10;
const uint16_t SENSOR_FZ = 12;

static std::map<int ,int> sensorsMap =
{
    {1, SENSOR_YAW},
    {2, SENSOR_PITCH},
    {3, SENSOR_ROLL},
    {4, SENSOR_TX},
    {5, SENSOR_TY},
    {6, SENSOR_FZ},
    {7, SENSOR_UCH0},
    {8, SENSOR_UCH1},
    {9, SENSOR_UCH2},
    {10, SENSOR_UCH3},
    {11, SENSOR_UCH0},
    {12, SENSOR_UCH1},
    {13, SENSOR_UCH2},
    {14, SENSOR_UCH3}
};

enum Powers
{
    Power12V,
    Power6V1,
    Power6V2,
    Power8V1,
    Power8V2,
    Power48V
};

const uint16_t DEVICE_CHANNEL =  0;

const uint16_t MOTOR_STATE =     1;
const uint16_t MOTOR_ANGLE =     2;
const uint16_t MOTOR_VOLTAGE =   4;
const uint16_t MOTOR_CURRENT =   6;
const uint16_t MOTOR_SHIFT  =    6;
const uint16_t MOTOR_P_GATE =    8;
const uint16_t MOTOR_I_GATE =    10;
const uint16_t MOTOR_D_GATE =    4;
const uint16_t MOTOR_MIN_ANGLE = 12;
const uint16_t MOTOR_MAX_ANGLE = 14;

const uint16_t POWER_ADDRESS = 1408;

const uint16_t POWER_VOLTAGE_6_1 =   0 * 2 + POWER_ADDRESS;
const uint16_t POWER_VOLTAGE_6_2 =   1 * 2 + POWER_ADDRESS;
const uint16_t POWER_VOLTAGE_8_1 =   2 * 2 + POWER_ADDRESS;
const uint16_t POWER_VOLTAGE_8_2 =   3 * 2 + POWER_ADDRESS;
const uint16_t POWER_VOLTAGE_12 =    4 * 2 + POWER_ADDRESS;
const uint16_t POWER_VOLTAGE_48 =    5 * 2 + POWER_ADDRESS;

const uint16_t POWER_CURRENT_6_1 =   0 * 2 + 12 + POWER_ADDRESS;
const uint16_t POWER_CURRENT_6_2 =   1 * 2 + 12 + POWER_ADDRESS;
const uint16_t POWER_CURRENT_8_1 =   2 * 2 + 12 + POWER_ADDRESS;
const uint16_t POWER_CURRENT_8_2 =   3 * 2 + 12 + POWER_ADDRESS;
const uint16_t POWER_CURRENT_12 =    4 * 2 + 12 + POWER_ADDRESS;
const uint16_t POWER_CURRENT_48 =    5 * 2 + 12 + POWER_ADDRESS;

struct PowerStateAddress
{
    int PowerVoltageAddress;
    int PowerCurrentAddress;
};

static std::map<int ,PowerStateAddress> powerStateMap =
{
    {Power12V, {POWER_VOLTAGE_12, POWER_CURRENT_12}},
    {Power6V1, {POWER_VOLTAGE_6_1, POWER_CURRENT_6_1}},
    {Power6V2, {POWER_VOLTAGE_6_2, POWER_CURRENT_6_2}},
    {Power8V1, {POWER_VOLTAGE_8_1, POWER_CURRENT_8_1}},
    {Power8V2, {POWER_VOLTAGE_8_2, POWER_CURRENT_8_2}},
    {Power48V, {POWER_VOLTAGE_48, POWER_CURRENT_48}}
};

#endif // AR60XPACKETDEFINITION_H
