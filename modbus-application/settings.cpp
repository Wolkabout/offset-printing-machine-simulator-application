#include <QNetworkInterface>
#include "settings.h"
#include "ui_settings.h"

Settings::Settings(Simulator& simulator, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Settings),
    simulator(simulator)
{
    ui->setupUi(this);

    modbus = modbus_new_tcp("127.0.0.1", 502);

    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
             addressString += address.toString();
    }

    ui->ip->setText(addressString);
}

Settings::~Settings()
{
    delete ui;
}
