#pragma once
class JointState
{
public:

	// Состояние узлов (моторов)
	enum JOINT_STATES
	{
		BRAKE, // мотор обесточен, муфта заблокирована
		STOP, // мотор включен, муфта разблокированна
		RELAX, // мотор обесточен, мефта разблокированна
		TRACE // мотор управляется углом
	};

	JointState();
	~JointState();
};

