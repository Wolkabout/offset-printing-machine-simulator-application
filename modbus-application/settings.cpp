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
    modbus_set_debug(modbus, TRUE);
    mapping = modbus_mapping_new(0x1E, 0x1E, 0x1E, 0x1E);

    modbus_set_response_timeout(modbus, 60, 0);

    ui->ip->setText(addressString);

    if (mapping == nullptr) {
        qDebug("The mapping couldn\'t be allocated!");
        modbus_free(modbus);
        return;
    }

    printMappings();

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
    uint8_t * tab_bits = mapping->tab_bits;
    uint8_t * tab_input_bits = mapping->tab_input_bits;
    uint16_t * tab_registers = mapping->tab_registers;
    uint16_t * tab_input_registers = mapping->tab_input_registers;
    for (int i = 0; i < 30; i++) {
        qDebug(std::string(std::to_string(i) + " "
                           + std::to_string(tab_bits[i]) + " "
                           + std::to_string(tab_input_bits[i]) + " "
                           + std::to_string(tab_registers[i]) + " "
                           + std::to_string(tab_input_registers[i])).c_str());
    }
}
