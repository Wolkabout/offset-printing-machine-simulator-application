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

    ui->clock->setText(QTime::currentTime().toString("hh:mm"));
    ui->date->setText(QDate::currentDate().toString());
    startTimer(100);

//    uncomment when building for RPi
//    QMainWindow::showFullScreen();
}

MainWindow::MainViewStateListener::MainViewStateListener(MainWindow& mainWindow) : mainWindow(mainWindow) { }

void MainWindow::MainViewStateListener::ReceiveMachineState(bool x)
{
    if (x) {

    } else {

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
