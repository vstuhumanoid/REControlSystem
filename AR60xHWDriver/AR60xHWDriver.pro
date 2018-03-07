#-------------------------------------------------
#
# Project created by QtCreator 2018-03-04T01:45:13
#
#-------------------------------------------------

QT       -= gui

TARGET = AR60xHWDriver
TEMPLATE = lib
CONFIG += staticlib qt c++14 thread

SOURCES += AR60xHWDriver.cpp \
    RobotDescription/AR60xDescription.cpp \
    RobotDescription/JointInformation.cpp \
    RobotDescription/SensorInformation.cpp \
    RobotDescription/JSONSerializer.cpp \
    Elements/AdditionalSettings.cpp \
    Elements/JointSettings.cpp \
    Elements/JointState.cpp \
    Elements/PowerSettings.cpp \
    Elements/PowerState.cpp \
    Elements/SensorState.cpp

HEADERS += AR60xHWDriver.h \
    RobotDescription/AR60xDescription.h \
    RobotDescription/JointInformation.h \
    RobotDescription/SensorInformation.h \
    RobotDescription/JSONSerializer.h \
    Libs/JSON/json.hpp \
    HardwareInterfaces/IAR60xJointControl.h \
    HardwareInterfaces/IAR60xJointState.h \
    HardwareInterfaces/IAR60xPowerControl.h \
    HardwareInterfaces/IAR60xPowerState.h \
    HardwareInterfaces/IAR60xSensorState.h \
    Elements/AdditionalSettings.h \
    Elements/JointSettings.h \
    Elements/JointState.h \
    Elements/PowerSettings.h \
    Elements/PowerState.h \
    Elements/SensorState.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
