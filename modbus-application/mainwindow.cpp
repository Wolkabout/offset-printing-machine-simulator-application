#include "logs.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(Simulator &simulator, QWidget *parent) :
    QMainWindow(parent),
    simulator(simulator),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
