#include <QNetworkInterface>
#include "settings.h"
#include "ui_settings.h"
#include <modbus/modbus.h>
#include <modbus/modbus-tcp.h>

Settings::Settings(Simulator& simulator, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Settings),
    simulator(simulator)
{
    ui->setupUi(this);

    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
             addressString += address.toString();
    }

    modbus = modbus_new_tcp(addressString.toStdString().c_str(), 502);
    mapping = modbus_mapping_new(30, 30, 30, 30);

    ui->ip->setText(addressString);

    if (mapping == nullptr) {
        qDebug("The mapping couldn\'t be allocated!");
        modbus_free(modbus);
        return;
    }

    thread = new ModbusThread(modbus, mapping);
    thread->start();
}

Settings::~Settings()
{
    modbus_mapping_free(mapping);
    modbus_close(modbus);
    modbus_free(modbus);

    delete ui;
}
