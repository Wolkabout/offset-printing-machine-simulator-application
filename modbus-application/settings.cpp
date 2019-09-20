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

    ui->ip->setText(addressString);

    modbus = modbus_new_tcp("127.0.0.1", 502);
    mapping = modbus_mapping_new(30, 30, 30, 30);

    if (mapping == nullptr) {
        qDebug("The mapping couldn\'t be allocated!");
        modbus_free(modbus);
        return;
    }

    int listen = modbus_tcp_listen(modbus, 1);
    modbus_tcp_accept(modbus, &listen);

    modbus_mapping_free(mapping);
    modbus_close(modbus);
    modbus_free(modbus);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::loop() {
    while (true) {

    }
}
