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
    driver->PowerSetState(PowerSettings::Power12V, true);

    int lowerLimit = driver->getRobotDesc()->getJoints()->at(1).limits.lowerLimit;

    ui->horizontalSlider->setMinimum(driver->getRobotDesc()->getJoints()->at(1).limits.lowerLimit);
    ui->horizontalSlider->setMaximum(driver->getRobotDesc()->getJoints()->at(1).limits.upperLimit);
    ui->horizontalSlider->setValue(0);

    qDebug() << "joint 1 prepaired for trace" << endl;
}

MainWindow::~MainWindow()
{
    driver->robotDisconnect();
    qDebug() << "disconnected success" << endl;
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    driver->JointSetPosition(1, driver->JointGetPosition(1));
    driver->JointSetState(1, JointState::JOINT_STATES::TRACE);
    qDebug() << "joint 1 set for trace" << endl;
}

void MainWindow::on_ButtonOn_clicked()
{
   driver->PowerSetState(PowerSettings::Power6V1, true);
   driver->PowerSetState(PowerSettings::Power6V2, true);
   driver->PowerSetState(PowerSettings::Power8V1, true);
   driver->PowerSetState(PowerSettings::Power8V2, true);
   driver->PowerSetState(PowerSettings::Power48V, true);
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    driver->JointSetPosition(1, position);
}
