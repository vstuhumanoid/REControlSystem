#include "mainwindow.h"
#include <QApplication>

#include "RobotDriver/AR60xUDPPortMaster.h"

void getMaster (IPortMaster& master)
{
    char * array = new char[100];
    master.Read(array);
}

int main(int argc, char *argv[])
{
    AR60xUDPPortMaster master;
    getMaster(master);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}


