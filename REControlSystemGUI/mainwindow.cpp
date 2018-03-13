#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _logger = new Logger();
    driver = new AR60xHWDriver(_logger);

    //driver->loadConfig("config_backup.xml");
    //driver->saveConfig("config_to.xml");

    bool isOk = driver->loadConfig("config_backup.xml");

    if(!isOk)
    {
        qDebug() << "load config file failed" << endl;
        exit(0);
    }
    else
    {
        qDebug() << "load config file success" << endl;
    }

    driver->initPackets();

    qDebug() << "init packets success" << endl;

    driver->robotConnect();
    driver->SupplySetState(PowerData::Supply12V, true);

    int lowerLimit = driver->getRobotDesc()->getJoints()->at(1).limits.lowerLimit;
    int upperLimit = driver->getRobotDesc()->getJoints()->at(1).limits.upperLimit;

    ui->horizontalSlider->setMinimum(lowerLimit);
    ui->horizontalSlider->setMaximum(upperLimit);
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
    driver->JointSetState(1, JointState::TRACE);
    qDebug() << "joint 1 set for trace" << endl;
}

void MainWindow::on_ButtonOn_clicked()
{
   driver->SupplySetState(PowerData::Supply6V1, true);
   driver->SupplySetState(PowerData::Supply6V2, true);
   driver->SupplySetState(PowerData::Supply8V1, true);
   driver->SupplySetState(PowerData::Supply8V2, true);
   driver->SupplySetState(PowerData::Supply48V, true);
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    driver->JointSetPosition(1, position);
}
