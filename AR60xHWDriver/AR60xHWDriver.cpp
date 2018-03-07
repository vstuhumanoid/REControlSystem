#include "AR60xHWDriver.h"


AR60xHWDriver::AR60xHWDriver()
{
    desc = new AR60xDescription();
}

void AR60xHWDriver::saveDesc(std::__cxx11::string fileName)
{
    JointInformation joint;
    joint.channel = 2;
    joint.isEnable = false;
    joint.isReverce = false;
    joint.jointName = "joint 1";
    joint.offset = 34455;
    joint.jointNumber = 1;

    JointInformation::PIDGates gates;
    gates.diffGate = 5;
    gates.intGate = 6;
    gates.propGate = 1200;

    joint.gates = gates;

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

    gates.diffGate = 5;
    gates.intGate = 6;
    gates.propGate = 1200;

    joint2.gates = gates;

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

    JSONSerializer serializer;
    serializer.setDesc(desc);
    serializer.serialize(fileName);
}
