#-------------------------------------------------
#
# Project created by QtCreator 2018-03-13T13:07:50
#
#-------------------------------------------------

QT       -= gui

TARGET = REControlSystemInterfaces
TEMPLATE = lib
CONFIG += staticlib

SOURCES += REControlSystemInterfaces.cpp

HEADERS += REControlSystemInterfaces.h \
    ILogger.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
