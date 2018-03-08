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
        jointSetPropGate(joint.jointNumber, joint.gates.propGate);
        jointSetIntGate(joint.jointNumber, joint.gates.intGate);
        jointSetDiffGate(joint.jointNumber, joint.gates.diffGate);
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
    writeInt16(channel * 16 + MOTOR_ANGLE, value);
    locker.unlock();
}

void AR60xSendPacket::jointSetOffset(short number, short value)
{
    locker.lock();
    short channel = desc->joints.at(number).channel;
    writeInt16(channel * 16 + MOTOR_SHIFT, value);
    locker.unlock();
}

void AR60xSendPacket::jointSetPropGate(short number, short value)
{
    locker.lock();
    short channel = desc->joints.at(number).channel;
    writeInt16(channel * 16 + MOTOR_P_GATE, value);
    locker.unlock();
}

void AR60xSendPacket::jointSetIntGate(short number, short value)
{
    locker.lock();
    short channel = desc->joints.at(number).channel;
    writeInt16(channel * 16 + MOTOR_I_GATE, value);
    locker.unlock();
}

void AR60xSendPacket::jointSetDiffGate(short number, short value)
{
    locker.lock();
    short channel = desc->joints.at(number).channel;
    writeInt16(channel * 16 + MOTOR_D_GATE, value);
    locker.unlock();
}

void AR60xSendPacket::jointSetLowerLimit(short number, short value)
{
    locker.lock();
    short channel = desc->joints.at(number).channel;
    bool isReverce = desc->joints.at(number).isReverce;
    if(isReverce)
        writeInt16(channel * 16 + MOTOR_MAX_ANGLE, -1 * value);
    else
        writeInt16(channel * 16 + MOTOR_MIN_ANGLE, value);
    locker.unlock();
}

void AR60xSendPacket::jointSetUpperLimit(short number, short value)
{
    locker.lock();
    short channel = desc->joints.at(number).channel;
    bool isReverce = desc->joints.at(number).isReverce;
    if(isReverce)
        writeInt16(channel * 16 + MOTOR_MIN_ANGLE, -1 * value);
    else
        writeInt16(channel * 16 + MOTOR_MAX_ANGLE, value);
    locker.unlock();
}

void AR60xSendPacket::jointSetState(short number, JointState::JOINT_STATES state)
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

void AR60xSendPacket::PowerSetOff(Powers power)
{
    switch (power) {
    case Power12V:
    {
        byteArray[POWER_ADDRESS + 1] &= (255-16);
    }
        break;
    case Power6V1:
    {
        byteArray[POWER_ADDRESS + 1] &= (255-1);
    }
        break;
    case Power6V2:
    {
        byteArray[POWER_ADDRESS + 1] &= (255-2);
    }
        break;
    case Power8V1:
    {
        byteArray[POWER_ADDRESS + 1] &= (255-4);
    }
        break;
    case Power8V2:
    {
        byteArray[POWER_ADDRESS + 1] &= (255-8);
    }
        break;
    case Power48V:
    {
        byteArray[POWER_ADDRESS + 1] &= (255-32);
    }
        break;
    default:
        break;
    }
}

void AR60xSendPacket::PowerSetOn(Powers power)
{
    switch (power) {
    case Power12V:
    {
        byteArray[POWER_ADDRESS + 1] |= 16;
    }
        break;
    case Power6V1:
    {
        byteArray[POWER_ADDRESS + 1] |= 1;
    }
        break;
    case Power6V2:
    {
        byteArray[POWER_ADDRESS + 1] |= 2;
    }
        break;
    case Power8V1:
    {
        byteArray[POWER_ADDRESS + 1] |= 4;
    }
        break;
    case Power8V2:
    {
        byteArray[POWER_ADDRESS + 1] |= 8;
    }
        break;
    case Power48V:
    {
        byteArray[POWER_ADDRESS + 1] |= 32;
    }
        break;
    default:
        break;
    }
}


