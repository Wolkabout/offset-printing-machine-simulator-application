#include "logs.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QTime>
#include <QTimer>
#include <qdatetime.h>

MainWindow::MainWindow(Simulator &simulator, QWidget *parent) :
    QMainWindow(parent),
    simulator(simulator),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->clock->setText(QTime::currentTime().toString("hh:mm"));
    ui->date->setText(QDate::currentDate().toString());
    startTimer(100);

//    uncomment when building for RPi
//    QMainWindow::showFullScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Logs* logs = new Logs(ui->displayedWindow);
    logs->show();
//    QMessageBox box(this);
//    box.setText("Hello World!");
//    box.exec();
}

void MainWindow::timerEvent(QTimerEvent *event) {
    ui->clock->setText(QTime::currentTime().toString("hh:mm"));
    ui->date->setText(QDate::currentDate().toString("dddd, d. MMMM yyyy"));
}
