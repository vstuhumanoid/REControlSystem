#-------------------------------------------------
#
# Project created by QtCreator 2018-03-04T01:45:13
#
#-------------------------------------------------

QT -= gui
QT += network
QT += core
QT += xml

TARGET = AR60xHWDriver
TEMPLATE = lib
CONFIG += staticlib qt c++11 thread

SOURCES += AR60xHWDriver.cpp \
    RobotDescription/AR60xDescription.cpp \
    RobotPackets/AR60xRecvPacket.cpp \
    RobotPackets/AR60xSendPacket.cpp \
    UDPConnection.cpp \
    DataTypes/JointState.cpp \
    DataTypes/PowerState.cpp \
    DataTypes/SensorState.cpp \
    DataTypes/JointData.cpp \
    DataTypes/PowerData.cpp \
    DataTypes/SensorData.cpp \
    DataTypes/ConnectionData.cpp \
    XMLSerializer.cpp \
    Libs/TinyXML2/tinyxml2.cpp \
    Libs/TinyXML2/xmltest.cpp

HEADERS += AR60xHWDriver.h \
    RobotDescription/AR60xDescription.h \
    HardwareInterfaces/IAR60xJointControl.h \
    HardwareInterfaces/IAR60xJointState.h \
    HardwareInterfaces/IAR60xPowerState.h \
    HardwareInterfaces/IAR60xSensorState.h \
    RobotPackets/AR60xPacketsDefinitions.h \
    RobotPackets/AR60xRecvPacket.h \
    RobotPackets/AR60xSendPacket.h \
    UDPConnection.h \
    DataTypes/JointState.h \
    DataTypes/PowerState.h \
    DataTypes/SensorState.h \
    DataTypes/JointData.h \
    DataTypes/PowerData.h \
    DataTypes/SensorData.h \
    HardwareInterfaces/IAR60xPowerControl.h \
    DataTypes/ConnectionData.h \
    XMLSerializer.h \
    Libs/TinyXML2/tinyxml2.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
