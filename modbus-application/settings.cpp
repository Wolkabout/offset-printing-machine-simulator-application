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
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost) {
             addressString += address.toString();
             break;
        }
    }

    modbus = modbus_new_tcp(addressString.toStdString().c_str(), 502);
    modbus_set_debug(modbus, TRUE);

    modbus_set_response_timeout(modbus, 60, 0);

    ui->ip->setText(addressString);

    if (mapping == nullptr) {
        qDebug("The mapping couldn\'t be allocated!");
        modbus_free(modbus);
        return;
    }

//    printMappings();

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

void Settings::printMappings() {
    try {
        qDebug("tab_bits | starting at %#x", mapping->tab_bits);
        for (int i = 0; i < 30; i++)
            qDebug("%#x %u", (mapping->tab_bits + (sizeof(uint8_t) * i)), mapping->tab_bits[i]);

        qDebug("tab_input_bits | starting at %#x", mapping->tab_input_bits);
        for (int i = 0; i < 30; i++)
            qDebug("%#x %u", (mapping->tab_input_bits + (sizeof(uint8_t) * i)), mapping->tab_input_bits[i]);

        qDebug("tab_registers | starting at %#x", mapping->tab_registers);
        for (int i = 0; i < 30; i++)
            qDebug("%#x %u", (mapping->tab_registers + (sizeof(uint16_t) * i)), mapping->tab_registers[i]);

        qDebug("tab_input_registers | %#x", mapping->tab_input_registers);
        for (int i = 0; i < 30; i++)
            qDebug("%#x %u", (mapping->tab_input_registers + (sizeof(uint16_t) * i)), mapping->tab_input_registers[i]);
    } catch (std::exception &e) {
        qDebug("%s", e.what());
    }
}
