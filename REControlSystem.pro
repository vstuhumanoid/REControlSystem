#-------------------------------------------------
#
# Project created by QtCreator 2018-01-09T19:56:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = REControlSystem
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    RobotDriver/AR60xSendPacket.cpp \
    RobotDriver/AR60xRecvPacket.cpp \
    RobotDriver/AR60xUDPPortMaster.cpp

HEADERS  += mainwindow.h \
    RobotDriver/AR60xSendPacket.h \
    RobotDriver/AR60xRecvPacket.h \
    RobotDriver/IPortMaster.h \
    RobotDriver/AR60xUDPPortMaster.h \
    RobotDriver/AR60xPacketsDefinitions.h

FORMS    += mainwindow.ui
