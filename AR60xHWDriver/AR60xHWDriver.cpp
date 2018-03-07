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
    serializer.deserialize(fileName);
}

void AR60xHWDriver::generateDesc(std::string fileName)
{
    JointInformation joint;

    joint.jointNumber = 1;
    joint.channel = 1;
    joint.jointName = "Стопа Y (R)";
    joint.offset = -114;
    joint.gates.propGate = 900;
    joint.gates.intGate = 2;
    joint.gates.diffGate = 1;
    joint.limits.lowerLimit = -1500;
    joint.limits.upperLimit = 1500;
    joint.isReverce = false;
    joint.isEnable = true;

    desc->joints[joint.jointNumber] = joint;

    joint.jointNumber = 2;
    joint.channel = 2;
    joint.jointName = "Стопа X (R)";
    joint.offset = -5361;
    joint.gates.propGate = 900;
    joint.gates.intGate = 2;
    joint.gates.diffGate = 1;
    joint.limits.lowerLimit = -4000;
    joint.limits.upperLimit = 8000;
    joint.isReverce = false;
    joint.isEnable = true;

    desc->joints[joint.jointNumber] = joint;

    joint.jointNumber = 3;
    joint.channel = 3;
    joint.jointName = "Колено (R)";
    joint.offset = -7804;
    joint.gates.propGate = 900;
    joint.gates.intGate = 2;
    joint.gates.diffGate = 1;
    joint.limits.lowerLimit = -10000;
    joint.limits.upperLimit = 700;
    joint.isReverce = false;
    joint.isEnable = true;

    desc->joints[joint.jointNumber] = joint;

    joint.jointNumber = 4;
    joint.channel = 4;
    joint.jointName = "Бедро X (R)";
    joint.offset = 4851;
    joint.gates.propGate = 900;
    joint.gates.intGate = 2;
    joint.gates.diffGate = 1;
    joint.limits.lowerLimit = -1000;
    joint.limits.upperLimit = 7500;
    joint.isReverce = true;
    joint.isEnable = true;

    desc->joints[joint.jointNumber] = joint;

    joint.jointNumber = 5;
    joint.channel = 5;
    joint.jointName = "Бедро Y (R)";
    joint.offset = 193;
    joint.gates.propGate = 900;
    joint.gates.intGate = 2;
    joint.gates.diffGate = 1;
    joint.limits.lowerLimit = -1400;
    joint.limits.upperLimit = 1500;
    joint.isReverce = true;
    joint.isEnable = true;

    desc->joints[joint.jointNumber] = joint;

    joint.jointNumber = 6;
    joint.channel = 6;
    joint.jointName = "Бедро вращение (R)";
    joint.offset = 8208;
    joint.gates.propGate = 900;
    joint.gates.intGate = 2;
    joint.gates.diffGate = 1;
    joint.limits.lowerLimit = -1000;
    joint.limits.upperLimit = 1000;
    joint.isReverce = true;
    joint.isEnable = true;

    desc->joints[joint.jointNumber] = joint;

    joint.jointNumber = 7;
    joint.channel = 7;
    joint.jointName = "Стопа Y (L)";
    joint.offset = 6389;
    joint.gates.propGate = 900;
    joint.gates.intGate = 2;
    joint.gates.diffGate = 1;
    joint.limits.lowerLimit = -1500;
    joint.limits.upperLimit = 1500;
    joint.isReverce = true;
    joint.isEnable = true;

    desc->joints[joint.jointNumber] = joint;

    joint.jointNumber = 8;
    joint.channel = 8;
    joint.jointName = "Стопа X (L)";
    joint.offset = -870;
    joint.gates.propGate = 900;
    joint.gates.intGate = 2;
    joint.gates.diffGate = 1;
    joint.limits.lowerLimit = -4000;
    joint.limits.upperLimit = 8000;
    joint.isReverce = true;
    joint.isEnable = true;

    desc->joints[joint.jointNumber] = joint;

    joint.jointNumber = 9;
    joint.channel = 9;
    joint.jointName = "Колено (L)";
    joint.offset = -4965;
    joint.gates.propGate = 900;
    joint.gates.intGate = 2;
    joint.gates.diffGate = 1;
    joint.limits.lowerLimit = -10000;
    joint.limits.upperLimit = 700;
    joint.isReverce = true;
    joint.isEnable = true;

    desc->joints[joint.jointNumber] = joint;

    joint.jointNumber = 10;
    joint.channel = 10;
    joint.jointName = "Бедро X (L)";
    joint.offset = -4429;
    joint.gates.propGate = 900;
    joint.gates.intGate = 2;
    joint.gates.diffGate = 1;
    joint.limits.lowerLimit = -1000;
    joint.limits.upperLimit = 7500;
    joint.isReverce = false;
    joint.isEnable = true;

    desc->joints[joint.jointNumber] = joint;

    joint.jointNumber = 11;
    joint.channel = 11;
    joint.jointName = "Бедро Y (L)";
    joint.offset = 4218;
    joint.gates.propGate = 900;
    joint.gates.intGate = 2;
    joint.gates.diffGate = 1;
    joint.limits.lowerLimit = -1400;
    joint.limits.upperLimit = 1500;
    joint.isReverce = false;
    joint.isEnable = true;

    desc->joints[joint.jointNumber] = joint;

    joint.jointNumber = 12;
    joint.channel = 12;
    joint.jointName = "Бедро вращение (L)";
    joint.offset = 7664;
    joint.gates.propGate = 900;
    joint.gates.intGate = 2;
    joint.gates.diffGate = 1;
    joint.limits.lowerLimit = -1000;
    joint.limits.upperLimit = 1000;
    joint.isReverce = false;
    joint.isEnable = true;

    desc->joints[joint.jointNumber] = joint;

    JSONSerializer serializer;
    serializer.setDesc(desc);
    serializer.serialize(fileName);
}
