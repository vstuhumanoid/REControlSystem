#include "AR60xDriver.h"



AR60xDriver::AR60xDriver()
{
}


AR60xDriver::~AR60xDriver()
{
}

void AR60xDriver::setSettings(AdditionalSettings settings)
{
}

void AR60xDriver::getSettings(AdditionalSettings & settings)
{
}

void AR60xDriver::JointSetPosition(int joint, int position)
{
}

void AR60xDriver::JointsSetPositions(int joints[], int positions[])
{
}

void AR60xDriver::JointSetSettings(int joint, JointSettings settings)
{
}

void AR60xDriver::JointSetState(JointState state)
{
}

int AR60xDriver::JointGetPosition(int joint)
{
	return 0;
}

void AR60xDriver::JointsGetPositions(int joints[], int positions[])
{
}

void AR60xDriver::JointGetSettings(int joint, JointSettings & settings)
{
}

JointState AR60xDriver::JointGetState(int joint)
{
	return JointState();
}

void AR60xDriver::PowerSetSettings(PowerSettings settings)
{
}

void AR60xDriver::PowerGetState(PowerState & state)
{
}

void AR60xDriver::SensorGetState(int sensor, SensorState & state)
{
}
