#include "AR60xSendPacket.h"

AR60xSendPacket::AR60xSendPacket(AR60xDescription *robotDesc)
{
    desc = robotDesc;
}

void AR60xSendPacket::initFromByteArray(unsigned char bytes[])
{
    locker.lock();
    for(int i = 0; i < packetSize; i++)
        byteArray[i] = bytes[i];
    locker.unlock();
}

void AR60xSendPacket::init()
{
    for(int i = 0; i < packetSize; i++)  byteArray[i] = 0;
    for(auto it = desc->joints.begin(); it != desc->joints.end();++it)
    {
        JointInformation joint = (*it).second;
        writeInt16(joint.channel * 16, joint.jointNumber);
        jointSetPGain(joint.jointNumber, joint.gains.proportional);
        jointSetIGain(joint.jointNumber, joint.gains.integral);
        jointSetDGain(joint.jointNumber, joint.gains.derivative);
        jointSetOffset(joint.jointNumber, joint.offset);

        jointSetLowerLimit(joint.jointNumber, joint.limits.lowerLimit);
        jointSetUpperLimit(joint.jointNumber, joint.limits.upperLimit);
        jointSetState(joint.jointNumber, JointState::STOP);
    }
}

const char *AR60xSendPacket::getByteArray()
{
    return byteArray;
}

std::mutex *AR60xSendPacket::getMutex()
{
    return &locker;
}

void AR60xSendPacket::writeInt16(uint16_t address, int16_t value)
{
    byteArray[address + 1] = (BYTE)(value >> 8);
    byteArray[address] = value;
}

void AR60xSendPacket::jointSetPosition(short number, short value)
{
    short lowerLimit = desc->joints.at(number).limits.lowerLimit;
    short upperLimit = desc->joints.at(number).limits.upperLimit;
    bool isReverce = desc->joints.at(number).isReverce;
    short channel = desc->joints.at(number).channel;

    if(value < lowerLimit)
    {
        value = lowerLimit;
    }
    else if(value > upperLimit)
    {
        value = upperLimit;
    }
    if(isReverce) value = -1 * value;
    locker.lock();
    writeInt16(channel * 16 + JointPositionAddress, value);
    locker.unlock();
}

void AR60xSendPacket::jointSetOffset(short number, short value)
{
    locker.lock();
    short channel = desc->joints.at(number).channel;
    writeInt16(channel * 16 + JointOffsetAddress, value);
    locker.unlock();
}

void AR60xSendPacket::jointSetPGain(short number, short value)
{
    locker.lock();
    short channel = desc->joints.at(number).channel;
    writeInt16(channel * 16 + JointPGainAddress, value);
    locker.unlock();
}

void AR60xSendPacket::jointSetIGain(short number, short value)
{
    locker.lock();
    short channel = desc->joints.at(number).channel;
    writeInt16(channel * 16 + JointIGaneAddress, value);
    locker.unlock();
}

void AR60xSendPacket::jointSetDGain(short number, short value)
{
    locker.lock();
    short channel = desc->joints.at(number).channel;
    writeInt16(channel * 16 + JointDGainAddress, value);
    locker.unlock();
}

void AR60xSendPacket::jointSetLowerLimit(short number, short value)
{
    locker.lock();
    short channel = desc->joints.at(number).channel;
    bool isReverce = desc->joints.at(number).isReverce;
    if(isReverce)
        writeInt16(channel * 16 + JointUpperLimitAddress, -1 * value);
    else
        writeInt16(channel * 16 + JointLowerLimitAddress, value);
    locker.unlock();
}

void AR60xSendPacket::jointSetUpperLimit(short number, short value)
{
    locker.lock();
    short channel = desc->joints.at(number).channel;
    bool isReverce = desc->joints.at(number).isReverce;
    if(isReverce)
        writeInt16(channel * 16 + JointLowerLimitAddress, -1 * value);
    else
        writeInt16(channel * 16 + JointUpperLimitAddress, value);
    locker.unlock();
}

void AR60xSendPacket::jointSetState(short number, JointState::JointStates state)
{
    locker.lock();
    short channel = desc->joints.at(number).channel;
    bool isEnable = desc->joints.at(number).isEnable;

    switch (state) {
    case JointState::BRAKE:
    {
        byteArray[channel * 16 + 1] &= (255 - 3);
    }
        break;
    case JointState::RELAX:
    {
        byteArray[channel * 16 + 1] &= (255 - 3);
        byteArray[channel * 16 + 1] |= 2;
    }
        break;
    case JointState::STOP:
    {
        byteArray[channel * 16 + 1] &= (255 - 3);
        byteArray[channel * 16 + 1] |= 1;
    }
        break;
    case JointState::TRACE:
    {
        if(isEnable) byteArray[channel * 16 + 1] |= 3;
    }
        break;
    default:
        break;
    }
    locker.unlock();
}

// TODO: Убрать switch
void AR60xSendPacket::PowerSetOff(PowerSettings::Powers power)
{
    switch (power) {
    case PowerSettings::Power12V:
    {
        byteArray[PowerDataAddress + 1] &= (255-16);
    }
        break;
    case PowerSettings::Power6V1:
    {
        byteArray[PowerDataAddress + 1] &= (255-1);
    }
        break;
    case PowerSettings::Power6V2:
    {
        byteArray[PowerDataAddress + 1] &= (255-2);
    }
        break;
    case PowerSettings::Power8V1:
    {
        byteArray[PowerDataAddress + 1] &= (255-4);
    }
        break;
    case PowerSettings::Power8V2:
    {
        byteArray[PowerDataAddress + 1] &= (255-8);
    }
        break;
    case PowerSettings::Power48V:
    {
        byteArray[PowerDataAddress + 1] &= (255-32);
    }
        break;
    default:
        break;
    }
}


// TODO: Убрать switch
void AR60xSendPacket::PowerSetOn(PowerSettings::Powers power)
{
    switch (power) {
    case PowerSettings::Power12V:
    {
        byteArray[PowerDataAddress + 1] |= 16;
    }
        break;
    case PowerSettings::Power6V1:
    {
        byteArray[PowerDataAddress + 1] |= 1;
    }
        break;
    case PowerSettings::Power6V2:
    {
        byteArray[PowerDataAddress + 1] |= 2;
    }
        break;
    case PowerSettings::Power8V1:
    {
        byteArray[PowerDataAddress + 1] |= 4;
    }
        break;
    case PowerSettings::Power8V2:
    {
        byteArray[PowerDataAddress + 1] |= 8;
    }
        break;
    case PowerSettings::Power48V:
    {
        byteArray[PowerDataAddress + 1] |= 32;
    }
        break;
    default:
        break;
    }
}


