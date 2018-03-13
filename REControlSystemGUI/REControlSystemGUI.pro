#-------------------------------------------------
#
# Project created by QtCreator 2018-03-04T01:40:54
#
#-------------------------------------------------

QT += gui
QT += network
QT += core
QT += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = REControlSystemGUI
TEMPLATE = app
CONFIG += qt c++14 thread

SOURCES += main.cpp\
        mainwindow.cpp \
    Logger.cpp

HEADERS  += mainwindow.h \
    Logger.h

FORMS    += mainwindow.ui

win32:
{
    LIBS += -L../../../BUILDS/REControlSystem/Build_AR60xHWDriver/debug/ -lAR60xHWDriver
    INCLUDEPATH += ../AR60xHWDriver/
}

unix:
{
    LIBS += -L../../../BUILDS/REControlSystem/Build_AR60xHWDriver/ -lAR60xHWDriver
    INCLUDEPATH += ../AR60xHWDriver/
}



