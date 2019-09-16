#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(Simulator &simulator, QWidget *parent) :
    QMainWindow(parent),
    simulator(simulator),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMainWindow::showFullScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QMessageBox box(this);
    box.setText("Hello World!");
    box.exec();
}
