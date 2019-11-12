#include <QFontDatabase>
#include <QMessageBox>
#include <QNetworkInterface>
#include "settings.h"
#include "ui_settings.h"
#include "utility.h"
#include <modbus/modbus.h>
#include <modbus/modbus-tcp.h>

Settings::Settings(Simulator& simulator, ModbusThread &thread, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Settings),
    simulator(simulator),
    thread(thread)
{
    ui->setupUi(this);

    QFont robotoBold18(QFontDatabase::applicationFontFamilies(2).at(0), 14, QFont::DemiBold);
    ui->title->setFont(robotoBold18);
    ui->title_2->setFont(robotoBold18);
    QFont robotoMedium14(QFontDatabase::applicationFontFamilies(0).at(0), 10, QFont::DemiBold);
    ui->ip_title->setFont(robotoMedium14);
    ui->label->setFont(robotoMedium14);
    ui->label_2->setFont(robotoMedium14);
    ui->label_3->setFont(robotoMedium14);
    ui->label_4->setFont(robotoMedium14);
    ui->label_5->setFont(robotoMedium14);
    ui->label_6->setFont(robotoMedium14);
    ui->label_7->setFont(robotoMedium14);
    QFont robotoMedium16(QFontDatabase::applicationFontFamilies(0).at(0), 12, QFont::DemiBold);
    ui->feeder->setFont(robotoMedium16);
    ui->tempo->setFont(robotoMedium16);
    ui->delivery->setFont(robotoMedium16);
    ui->cyan->setFont(robotoMedium16);
    ui->magenta->setFont(robotoMedium16);
    ui->yellow->setFont(robotoMedium16);
    ui->black->setFont(robotoMedium16);
    ui->cancel->setFont(robotoMedium16);
    ui->apply->setFont(robotoMedium16);
    QFont robotoMedium18(QFontDatabase::applicationFontFamilies(0).at(0), 14, QFont::DemiBold);
    ui->ip->setFont(robotoMedium18);
    QFont robotoRegular14(QFontDatabase::applicationFontFamilies(1).at(0), 10);
    ui->desc->setFont(robotoRegular14);
    ui->desc_2->setFont(robotoRegular14);

    addressString = Utility::getIp();
    ui->ip->setText(addressString);
}

Settings::~Settings()
{
    delete ui;
}

