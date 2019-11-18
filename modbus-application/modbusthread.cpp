#include <QObject>
#include <functional>
#include <math.h>
#include "modbusthread.h"
#include "modbusthread_listeners.h"
#include "utility.h"

ModbusThread::ModbusThread(Simulator& simulator) :
    logger("ModbusServer"),
    simulator(simulator),
    messageHandler(mapping, simulator)
{
    addressString = Utility::getIp();
    modbus = modbus_new_tcp(nullptr, 2222);
//    modbus_set_debug(modbus, TRUE);
    modbus_set_response_timeout(modbus, 0, 0);

    messageHandler.setCallback([&](std::vector<int> values) {
        if (onConfigurations != nullptr) {
            onConfigurations(values);
        }
    });

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

    auto values = Configurations::load();

    for (int i = 22; i <= 28; i++) {
        mapping->tab_registers[i] = values[i - 22];
    }
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

        while (true) {
            try {
                int rc;
                rc = modbus_receive(modbus, query);
                if (rc > 0) {
                    if (query[header_length] == 5 || query[header_length] == 6) {
                        // write (single) coil or register
                        uint8_t message[5];
                        for (int i = header_length; i < rc; i++) {
                            message[i - header_length] = query[i];
                        }
                        messageHandler.handleMessage(message);
                    } else if (query[header_length] == 16) {
                        qDebug("%i %i %i", query[header_length], query[header_length + 2], query[header_length + 4]);
                        // write holding registers
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

void ModbusThread::receiveConfigurations(std::vector<int> values)
{
    for (int i = 22; i <= 28; i++) {
        mapping->tab_registers[i] = values[i - 22];
    }
}

void ModbusThread::onReceiveConfigurations(std::function<void (std::vector<int>)> callback)
{
    onConfigurations = callback;
}
