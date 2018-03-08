#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    driver = new AR60xHWDriver();
    bool isOk = driver->loadConfig("config_default.json");

    if(!isOk)
    {
        qDebug() << "load config file failed" << endl;
    }
    else
    {
        qDebug() << "load config file succes" << endl;
    }

    driver->initPackets();

    qDebug() << "init packets succes" << endl;

    driver->robotConnect();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

}
