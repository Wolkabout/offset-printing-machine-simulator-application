#include <math.h>
#include "modbusthread.h"
#include "utility.h"

ModbusThread::ModbusThread(Simulator& simulator) : logger("ModbusServer"), simulator(simulator)
{
    addressString = Utility::getIp();
    modbus = modbus_new_tcp(addressString.toStdString().c_str(), 2222);
//    modbus_set_debug(modbus, TRUE);
    modbus_set_response_timeout(modbus, 0, 0);

    mapping = modbus_mapping_new(30, 30, 30, 30);
    if (mapping == nullptr) {
        logger.Log("The mapping couldn\'t be allocated!");
        this->~ModbusThread();
        return;
    }

    // Machine values
    receiveState(simulator.getMachine()->isRunning());

    // Conveyor static values
    mapping->tab_input_registers[1] = simulator.getConveyor()->getMaxRatePerHour();
    mapping->tab_input_registers[2] = simulator.getConveyor()->getMinRatePerHour();

    // Feeder static values
    mapping->tab_input_registers[4] = simulator.getFeeder()->getCapacity();

    // Delivery static values
    mapping->tab_input_registers[7] = simulator.getDelivery()->getCapacity();

    // Paint Stations static values
    mapping->tab_input_registers[10] = simulator.getCyanPaint()->getCapacity();
    mapping->tab_input_registers[13] = simulator.getMagentaPaint()->getCapacity();
    mapping->tab_input_registers[16] = simulator.getYellowPaint()->getCapacity();
    mapping->tab_input_registers[19] = simulator.getBlackPaint()->getCapacity();

//    printMappings();
}

ModbusThread::~ModbusThread() {
    terminate();
    if (mapping != nullptr)
        modbus_mapping_free(mapping);
    modbus_close(modbus);
    modbus_free(modbus);
}


modbus_mapping_t *ModbusThread::getMapping() const
{
    return mapping;
}

void ModbusThread::run() {
    int listen = modbus_tcp_listen(modbus, 1);
    if (listen < 1) {
        logger.Log("The program doesn\'t have permissions to run modbus server.");
        return;
    }

    int header_length = modbus_get_header_length(modbus);
    query = new uint8_t[MODBUS_TCP_MAX_ADU_LENGTH] () ;

    while (true) {
//            this line is blocking! if there's no connection, it won't continue from here until one shows up!
        modbus_tcp_accept(modbus, &listen);
        logger.Log("Connection accepted.");

//            if the connection is successful
        while (true) {
            try {
                int rc;
                rc = modbus_receive(modbus, query);
//                qDebug("%i", rc);
                if (rc > 0) {
                    // printing the query
                    std::string message;
                    for (int i = header_length; i < rc; i++) {
                        message += std::to_string(query[i]) + ' ';
                    }
                    logger.Log(message);
                    modbus_reply(modbus, query, rc, mapping);
                } else if (rc == -1) {
                    logger.Log("Connection stopped.");
                    break;
                }
            } catch (std::exception &e) {
                logger.Log(e.what());
            }
        }
    }
}

void ModbusThread::printMappings() {
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

void ModbusThread::receiveState(bool state)
{
    mapping->tab_input_bits[0] = state;
    mapping->tab_bits[0] = state;
}

void ModbusThread::receiveCount(int tempoComponent, int count, double percentage)
{
    int capacityIndex = (tempoComponent * 3) + 4;
    int percentageIndex = capacityIndex + 1;
    int countIndex = percentageIndex + 1;

    mapping->tab_input_registers[percentageIndex] = std::round(percentage * 100);
    mapping->tab_input_registers[countIndex] = count;
}

void ModbusThread::receiveRate(int rate)
{
    mapping->tab_input_registers[3] = rate;
}
