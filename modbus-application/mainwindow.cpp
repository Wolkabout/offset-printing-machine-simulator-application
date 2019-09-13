#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Simulator &simulator, QWidget *parent) :
    QMainWindow(parent),
    simulator(simulator),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
