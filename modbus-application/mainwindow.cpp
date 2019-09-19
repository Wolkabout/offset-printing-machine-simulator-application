#include "feedercontrol.h"
#include "logs.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QTime>
#include <QTimer>
#include <qdatetime.h>

MainWindow::MainWindow(Simulator &simulator, WindowManager &windowManager, QWidget *parent) :
    QMainWindow(parent),
    simulator(simulator),
    windowManager(windowManager),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    uncomment when building for RPi
//    QMainWindow::showFullScreen();

    ui->clock->setText(QTime::currentTime().toString("hh:mm"));
    ui->date->setText(QDate::currentDate().toString());
    startTimer(100);

    listener = std::make_shared<MainViewStateListener>(*this);
    simulator.getMachine()->getExternalMachineStateReceivers().push_back(listener);
}

MainWindow::MainViewStateListener::MainViewStateListener(MainWindow& mainWindow) : mainWindow(mainWindow) { }

void MainWindow::MainViewStateListener::ReceiveMachineState(bool x)
{
    if (x) {
        mainWindow.ui->statusLabel->setText("Machine running.");
        mainWindow.ui->toggleButton->setText("Stop");
        mainWindow.ui->toggleButton->setStyleSheet("background-color: green; color: white;");
    } else {
        mainWindow.ui->statusLabel->setText("Machine not running.");
        mainWindow.ui->toggleButton->setText("Start");
        mainWindow.ui->toggleButton->setStyleSheet("background-color: red; color: white;");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

QFrame * MainWindow::frameHolder() {
    return ui->displayedWindow;
}

void MainWindow::timerEvent(QTimerEvent *event) {
    ui->clock->setText(QTime::currentTime().toString("hh:mm"));
    ui->date->setText(QDate::currentDate().toString("dddd, d. MMMM yyyy"));
}

void MainWindow::on_backButton_clicked()
{
    windowManager.goBack();
}

void MainWindow::on_homeButton_clicked()
{
    windowManager.hideEverything();
}

void MainWindow::on_logButton_clicked()
{
    windowManager.showFrame(0);
}

void MainWindow::on_settingsButton_clicked()
{
    windowManager.showFrame(1);
}

void MainWindow::on_machineButton_clicked()
{
    windowManager.showFrame(2);
}

void MainWindow::on_toggleButton_clicked()
{
    if (simulator.getMachine()->isRunning()) {
        simulator.getMachine()->stop();
    } else {
        simulator.getMachine()->start();
    }
}
