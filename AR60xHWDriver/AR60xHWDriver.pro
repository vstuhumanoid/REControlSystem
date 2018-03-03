#-------------------------------------------------
#
# Project created by QtCreator 2018-03-04T01:45:13
#
#-------------------------------------------------

QT       -= gui

TARGET = AR60xHWDriver
TEMPLATE = lib
CONFIG += staticlib

SOURCES += AR60xHWDriver.cpp

HEADERS += AR60xHWDriver.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
