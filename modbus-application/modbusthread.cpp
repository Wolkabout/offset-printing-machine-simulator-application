#include <math.h>
#include "modbusthread.h"
#include "modbusthread_listeners.h"
#include "utility.h"

ModbusThread::ModbusThread(Simulator& simulator) : logger("ModbusServer"), simulator(simulator), messageHandler(mapping, simulator)
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

    // Initial values
    // Machine values
    receiveState(simulator.getMachine()->isRunning());

    // Conveyor static values
    mapping->tab_input_registers[1] = simulator.getConveyor()->getMaxRatePerHour();
    mapping->tab_input_registers[2] = simulator.getConveyor()->getMinRatePerHour();
    receiveRate(simulator.getConveyor()->getRatePerHour());

    // Feeder static values
    mapping->tab_input_registers[4] = simulator.getFeeder()->getCapacity();
    receiveCount(0, simulator.getFeeder()->getCount(), std::round(simulator.getFeeder()->getPercentage()));

    // Delivery static values
    mapping->tab_input_registers[7] = simulator.getDelivery()->getCapacity();
    receiveCount(1, simulator.getDelivery()->getCount(), std::round(simulator.getDelivery()->getPercentage()));

    // Paint Stations static values
    mapping->tab_input_registers[10] = simulator.getCyanPaint()->getCapacity();
    receiveCount(2, simulator.getCyanPaint()->getCount(), std::round(simulator.getCyanPaint()->getPercentage()));

    mapping->tab_input_registers[13] = simulator.getMagentaPaint()->getCapacity();
    receiveCount(3, simulator.getMagentaPaint()->getCount(), std::round(simulator.getMagentaPaint()->getPercentage()));

    mapping->tab_input_registers[16] = simulator.getYellowPaint()->getCapacity();
    receiveCount(4, simulator.getYellowPaint()->getCount(), std::round(simulator.getYellowPaint()->getPercentage()));

    mapping->tab_input_registers[19] = simulator.getBlackPaint()->getCapacity();
    receiveCount(5, simulator.getBlackPaint()->getCount(), std::round(simulator.getBlackPaint()->getPercentage()));

    stateListener = std::make_shared<ModbusMachineStateListener>(*this);
    simulator.getMachine()->getExternalMachineStateReceivers().push_back(stateListener);

    feederListener = std::make_shared<ModbusCountListener>(*this, 0);
    simulator.getFeeder()->getCountMessageReceiver().push_back(feederListener);

    deliveryListener = std::make_shared<ModbusCountListener>(*this, 1);
    simulator.getDelivery()->getCountMessageReceiver().push_back(deliveryListener);

    cyanListener = std::make_shared<ModbusCountListener>(*this, 2);
    simulator.getCyanPaint()->getCountMessageReceiver().push_back(cyanListener);

    magentaListener = std::make_shared<ModbusCountListener>(*this, 3);
    simulator.getMagentaPaint()->getCountMessageReceiver().push_back(magentaListener);

    yellowListener = std::make_shared<ModbusCountListener>(*this, 4);
    simulator.getYellowPaint()->getCountMessageReceiver().push_back(yellowListener);

    blackListener = std::make_shared<ModbusCountListener>(*this, 5);
    simulator.getBlackPaint()->getCountMessageReceiver().push_back(blackListener);

    conveyorListener = std::make_shared<ModbusRateListener>(*this);
    simulator.getConveyor()->getRateMessageReceivers().push_back(conveyorListener);

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
                    if (query[header_length] == 2 || query[header_length] == 1 || query[header_length] == 23) {
                        std::string messageString;
                        for (int i = header_length; i < rc; i++) {
                            messageString += std::to_string(query[i]) + ' ';
                        }
                        qDebug(messageString.c_str());
                    }

                    if (query[header_length] == 5 || query[header_length] == 6) {
                        uint8_t message[5];
                        for (int i = header_length; i < rc; i++) {
                            message[i - header_length] = query[i];
                        }
                        messageHandler.handleMessage(message);
                    }
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
//    qDebug("%i %i %i", capacityIndex, percentageIndex, countIndex);

    mapping->tab_input_registers[percentageIndex] = std::round(percentage * 100);
    mapping->tab_input_registers[countIndex] = count;
}

void ModbusThread::receiveRate(int rate)
{
    mapping->tab_input_registers[3] = rate;
}
