#include "Machine/feedercontrol.h"
#include "Logs/logs.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QTime>
#include <QTimer>
#include <qdatetime.h>
#include <QFontDatabase>
#include <QPainter>

MainWindow::MainWindow(Simulator &simulator, QWidget *parent) :
    QMainWindow(parent),
    simulator(simulator),
    windowManager(),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Setup the background for the main window
    QPixmap background(":/Images/Background.svg");
    QPalette palette;
    palette.setBrush(QPalette::Background, background);
    setPalette(palette);

    // Setup the info bar
    QFont robotoMedium12(QFontDatabase::applicationFontFamilies(0).at(0), 9, QFont::DemiBold);
    ui->clock->setFont(robotoMedium12);
    ui->date->setFont(robotoMedium12);
    QFont robotoMedium16(QFontDatabase::applicationFontFamilies(0).at(0), 12, QFont::DemiBold);
    ui->label->setFont(robotoMedium16);
    ui->homeButton->setFont(robotoMedium16);
    ui->logButton->setFont(robotoMedium16);
    ui->machineButton->setFont(robotoMedium16);
    QFont robotoRegular16(QFontDatabase::applicationFontFamilies(1).at(0), 12);
    ui->welcomeText->setFont(robotoRegular16);

#ifdef QT_DEBUG
    // do nothing
#else
    QMainWindow::showFullScreen();
#endif

    ui->backButton->setIcon(QIcon(":/Icons/ico_back.svg"));
    ui->settingsButton->setIcon(QIcon(":/Icons/ico_settings.svg"));
    ui->logo->setPixmap(QPixmap(":/Images/Logo_white.svg"));

    QPixmap dimmer(":/Images/Dimmer.svg");
    QImage output(dimmer.size(), QImage::Format_ARGB32_Premultiplied);
    output.fill(Qt::transparent);
    QPainter painter(&output);
    painter.setOpacity(0.9);
    painter.drawPixmap(0, 0, dimmer);
    ui->fade->setPixmap(QPixmap::fromImage(output));

    ui->clock->setText(QTime::currentTime().toString("hh:mm"));
    ui->date->setText(QDate::currentDate().toString("dd.M.yyyy."));
    startTimer(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

WindowManager& MainWindow::getWindowManager() {
    return windowManager;
}

QFrame * MainWindow::frameHolder() {
    return ui->displayedWindow;
}

void MainWindow::windowActivationChange(bool oldChange)
{
    if (oldChange) {
        // not in focus
        ui->fade->show();
    } else {
        // in focus
        ui->fade->hide();
    }
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
