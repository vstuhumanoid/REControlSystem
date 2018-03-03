#pragma once

#include "IAR60xControl.h"

class AR60xDriver : IAR60xControl
{
public:
	AR60xDriver();
	~AR60xDriver();

	void setSettings(AdditionalSettings settings);
	void getSettings(AdditionalSettings &settings);

	void JointSetPosition(int joint, int position);
	void JointsSetPositions(int joints[], int positions[]);
	void JointSetSettings(int joint, JointSettings settings);
	void JointSetState(JointState state);

	int JointGetPosition(int joint);
	void JointsGetPositions(int joints[], int positions[]);
	void JointGetSettings(int joint, JointSettings & settings);
	JointState JointGetState(int joint);

	void PowerSetSettings(PowerSettings settings);

	void PowerGetState(PowerState & state);

	void SensorGetState(int sensor, SensorState & state);
};

