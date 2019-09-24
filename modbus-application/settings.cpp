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
    addressString = Utility::getIp();
    ui->ip->setText(addressString);
}

void Settings::on_debugMapping_clicked()
{
    QMessageBox messageBox(this);
    modbus_mapping_t * mapping = thread.getMapping();
    std::string bits, input_bits, registers, input_registers;
    for (int i = 0; i < 30; i++) {
        bits += std::to_string(mapping->tab_bits[i]) + ' ';
        input_bits += std::to_string(mapping->tab_input_bits[i]) + ' ';
        registers += std::to_string(mapping->tab_registers[i]) + ' ';
        input_registers += std::to_string(mapping->tab_input_registers[i]) + ' ';
    }
    bits += '\n';
    input_bits += '\n';
    registers += '\n';
    input_registers += '\n';
    messageBox.setText(QString::fromStdString(bits + input_bits + registers + input_registers));
    messageBox.exec();
}

Settings::~Settings()
{
    delete ui;
}

