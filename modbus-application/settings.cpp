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
    addressString = Utility::getIp();
    ui->ip->setText(addressString);
}

Settings::~Settings()
{
    delete ui;
}
