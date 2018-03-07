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
    RobotDescription/JSONSerializer.cpp

HEADERS += AR60xHWDriver.h \
    RobotDescription/AR60xDescription.h \
    RobotDescription/JointInformation.h \
    RobotDescription/SensorInformation.h \
    RobotDescription/JSONSerializer.h \
    Libs/JSON/json.hpp
unix {
    target.path = /usr/lib
    INSTALLS += target
}
