#include "feedercontrol.h"
#include "logs.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QTime>
#include <QTimer>
#include <qdatetime.h>
#include <QFontDatabase>

MainWindow::MainWindow(Simulator &simulator, WindowManager &windowManager, QWidget *parent) :
    QMainWindow(parent),
    simulator(simulator),
    windowManager(windowManager),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Setup the background for the main window
    QPixmap background(":/Images/Resources/Background.svg");
    QPalette palette;
    palette.setBrush(QPalette::Background, background);
    setPalette(palette);

    // Setup the info bar
    QFont robotoMedium12(QFontDatabase::applicationFontFamilies(0).at(0), 9, QFont::DemiBold);
    ui->clock->setFont(robotoMedium12);
    ui->date->setFont(robotoMedium12);
    QFont robotoMedium16(QFontDatabase::applicationFontFamilies(0).at(0), 12, QFont::DemiBold);
    ui->label->setFont(robotoMedium16);

//    uncomment when building for RPi
//    QMainWindow::showFullScreen();

    ui->backButton->setIcon(QIcon(":/Icons/Resources/ico_back.svg"));
    ui->settingsButton->setIcon(QIcon(":/Icons/Resources/ico_settings.svg"));
    ui->logo->setPixmap(QPixmap(":/Images/Resources/Logo_white.svg"));
    ui->welcomeText->setFont(robotoMedium16);
    ui->homeButton->setFont(robotoMedium16);
    ui->logButton->setFont(robotoMedium16);
    ui->machineButton->setFont(robotoMedium16);

    ui->clock->setText(QTime::currentTime().toString("hh:mm"));
    ui->date->setText(QDate::currentDate().toString());
    startTimer(100);
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
    ui->date->setText(QDate::currentDate().toString("dd.M.yyyy."));
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
