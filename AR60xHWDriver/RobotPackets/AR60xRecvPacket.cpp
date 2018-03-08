#include "AR60xRecvPacket.h"

AR60xRecvPacket::AR60xRecvPacket(AR60xDescription *robotDesc)
{
    desc = robotDesc;
}

void AR60xRecvPacket::initFromByteArray(const char bytes[])
{
    locker.lock();
    for(int i = 0; i < packetSize; i++)
        byteArray[i] = bytes[i];
    locker.unlock();
}

short AR60xRecvPacket::sensorGetValue(short number)
{
    locker.lock();
    int channel = desc->sensors.at(number).channel;
    int16_t value = readInt16(channel * 16 + sensorsMap.at(number));
    locker.unlock();
    return value;
}

int16_t AR60xRecvPacket::readInt16(uint16_t address)
{
    int16_t value = (byteArray[address + 1] << 8) + (BYTE)byteArray[address];
    return value;
}

float AR60xRecvPacket::readFloat(uint16_t address)
{
    float value = static_cast<float>((byteArray[address + 1] << 8) + (BYTE)byteArray[address]);
    return value;
}

short AR60xRecvPacket::jointGetCurrent(short number)
{
    locker.lock();
    int channel = desc->joints.at(number).channel;
    int16_t value = readInt16(channel * 16 + MOTOR_CURRENT);
    locker.unlock();
    return value;
}

short AR60xRecvPacket::jointGetVoltage(short number)
{
    locker.lock();
    int channel = desc->joints.at(number).channel;
    int16_t value = readInt16(channel * 16 + MOTOR_VOLTAGE);
    locker.unlock();
    return value;
}

short AR60xRecvPacket::jointGetPosition(short number)
{
    locker.lock();
    int channel = desc->joints.at(number).channel;
    int16_t value = readInt16(channel * 16 + MOTOR_ANGLE);
    locker.unlock();
    return value;
}

short AR60xRecvPacket::jointGetPropGate(short number)
{
    locker.lock();
    int channel = desc->joints.at(number).channel;
    int16_t value = readInt16(channel * 16 + MOTOR_P_GATE);
    locker.unlock();
    return value;
}

short AR60xRecvPacket::jointGetIntGate(short number)
{
    locker.lock();
    int channel = desc->joints.at(number).channel;
    int16_t value = readInt16(channel * 16 + MOTOR_I_GATE);
    locker.unlock();
    return value;
}

short AR60xRecvPacket::jointGetState(short number)
{
    locker.lock();
    int channel = desc->joints.at(number).channel;
    int16_t value = readInt16(channel * 16 + MOTOR_STATE);
    locker.unlock();
    return value;
}

short AR60xRecvPacket::jointGetLowerLimit(short number)
{
    int16_t value;
    locker.lock();
    int channel = desc->joints.at(number).channel;
    if(desc->joints.at(number).isReverce)
        value = -1 * readInt16(channel * 16 + MOTOR_MAX_ANGLE);
    else
        value = readInt16(channel * 16 + MOTOR_MIN_ANGLE);
    locker.unlock();
    return value;
}

short AR60xRecvPacket::jointGetUpperLimit(short number)
{
    int16_t value;
    locker.lock();
    int channel = desc->joints.at(number).channel;
    if(desc->joints.at(number).isReverce)
        value = -1 * readInt16(channel * 16 + MOTOR_MIN_ANGLE);
    else
        value = readInt16(channel * 16 + MOTOR_MAX_ANGLE);
    locker.unlock();
    return value;
}

float AR60xRecvPacket::powerGetVoltage(Powers power)
{
   locker.lock();
   int address = powerStateMap.at(power).PowerVoltageAddress;
   float value = readFloat(address) / 1000;
   if(address == POWER_VOLTAGE_48) value *= 10;
   locker.unlock();
   return value;
}

float AR60xRecvPacket::powerGetCurrent(Powers power)
{
    locker.lock();
    int address = powerStateMap.at(power).PowerCurrentAddress;
    float value = readFloat(address) / 1000;
    if(address == POWER_CURRENT_48) value *= 10;
    locker.unlock();
    return value;
}

const char *AR60xRecvPacket::getByteArray()
{
    return byteArray;
}

std::mutex *AR60xRecvPacket::getMutex()
{
    return &locker;
}




