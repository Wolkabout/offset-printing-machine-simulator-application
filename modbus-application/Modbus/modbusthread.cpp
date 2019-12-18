#include <QObject>
#include <functional>
#include <math.h>
#include <unistd.h>
#include "modbusthread.h"
#include "modbusthread_listeners.h"
#include "utility.h"

ModbusThread::ModbusThread(Simulator& simulator) :
    m_mapping(modbus_mapping_new(30, 30, 30, 30)),
    m_logger("ModbusServer"),
    m_simulator(simulator),
    m_messageHandler(m_mapping, m_simulator)
{
    m_addressString = Utility::getIp();
    m_modbus = modbus_new_tcp(nullptr, 2222);
//    modbus_set_debug(modbus, TRUE);
    modbus_set_response_timeout(m_modbus, 0, 0);

    m_messageHandler.setCallback([&](std::vector<int> values) {
        if (onConfigurations != nullptr) {
            onConfigurations(values);
        }
    });

    if (m_mapping == nullptr) {
        m_logger.Log("The mapping couldn\'t be allocated!");
        this->~ModbusThread();
        return;
    }

    // Initial values
    // Machine values
    receiveState(simulator.getMachine()->isRunning());

    // Conveyor static values
    m_mapping->tab_input_registers[1] = simulator.getConveyor()->getMaxRatePerHour();
    m_mapping->tab_input_registers[2] = simulator.getConveyor()->getMinRatePerHour();
    receiveRate(simulator.getConveyor()->getRatePerHour());

    // Feeder static values
    m_mapping->tab_input_registers[4] = simulator.getFeeder()->getCapacity();
    receiveCount(0, simulator.getFeeder()->getCount(), std::round(simulator.getFeeder()->getPercentage()));

    // Delivery static values
    m_mapping->tab_input_registers[7] = simulator.getDelivery()->getCapacity();
    receiveCount(1, simulator.getDelivery()->getCount(), std::round(simulator.getDelivery()->getPercentage()));

    // Paint Stations static values
    m_mapping->tab_input_registers[10] = simulator.getCyanPaint()->getCapacity();
    receiveCount(2, simulator.getCyanPaint()->getCount(), std::round(simulator.getCyanPaint()->getPercentage()));

    m_mapping->tab_input_registers[13] = simulator.getMagentaPaint()->getCapacity();
    receiveCount(3, simulator.getMagentaPaint()->getCount(), std::round(simulator.getMagentaPaint()->getPercentage()));

    m_mapping->tab_input_registers[16] = simulator.getYellowPaint()->getCapacity();
    receiveCount(4, simulator.getYellowPaint()->getCount(), std::round(simulator.getYellowPaint()->getPercentage()));

    m_mapping->tab_input_registers[19] = simulator.getBlackPaint()->getCapacity();
    receiveCount(5, simulator.getBlackPaint()->getCount(), std::round(simulator.getBlackPaint()->getPercentage()));

    m_stateListener = std::make_shared<ModbusMachineStateListener>(*this);
    simulator.getMachine()->getExternalMachineStateReceivers().push_back(m_stateListener);

    m_feederListener = std::make_shared<ModbusCountListener>(*this, 0);
    simulator.getFeeder()->getCountMessageReceiver().push_back(m_feederListener);

    m_deliveryListener = std::make_shared<ModbusCountListener>(*this, 1);
    simulator.getDelivery()->getCountMessageReceiver().push_back(m_deliveryListener);

    m_cyanListener = std::make_shared<ModbusCountListener>(*this, 2);
    simulator.getCyanPaint()->getCountMessageReceiver().push_back(m_cyanListener);

    m_magentaListener = std::make_shared<ModbusCountListener>(*this, 3);
    simulator.getMagentaPaint()->getCountMessageReceiver().push_back(m_magentaListener);

    m_yellowListener = std::make_shared<ModbusCountListener>(*this, 4);
    simulator.getYellowPaint()->getCountMessageReceiver().push_back(m_yellowListener);

    m_blackListener = std::make_shared<ModbusCountListener>(*this, 5);
    simulator.getBlackPaint()->getCountMessageReceiver().push_back(m_blackListener);

    m_conveyorListener = std::make_shared<ModbusRateListener>(*this);
    simulator.getConveyor()->getRateMessageReceivers().push_back(m_conveyorListener);

    auto values = Configurations::load();

    if (values.size() > 0) {
        for (int i = 22; i <= 28; i++) {
            m_mapping->tab_registers[i] = values[i - 22];
        }
    }
}

ModbusThread::~ModbusThread()
{
    m_shouldListen = false;
    if (m_mapping != nullptr)
        modbus_mapping_free(m_mapping);
    modbus_close(m_modbus);
    modbus_flush(m_modbus);
    modbus_free(m_modbus);
    m_modbus = nullptr;
}


modbus_mapping_t *ModbusThread::getMapping() const
{
    return m_mapping;
}

void ModbusThread::run() {
    int socket = modbus_tcp_listen(m_modbus, 1);
    if (socket < 1) {
        m_logger.Log("The program doesn\'t have permissions to run modbus server.");
        return;
    }

    fd_set set;
    timespec timeout;
    timeout.tv_sec = 1;
    timeout.tv_nsec = 0;

    modbus_set_response_timeout(m_modbus, 0, 200000);

    int header_length = modbus_get_header_length(m_modbus);
    m_query = new uint8_t[MODBUS_TCP_MAX_ADU_LENGTH] () ;
    m_shouldListen = true;

    while (m_shouldListen) {
        FD_ZERO(&set);
        FD_SET(socket, &set);
        int success = pselect(socket + 1, &set, nullptr, nullptr, &timeout, nullptr);

        if (success > 0) {
            modbus_tcp_accept(m_modbus, &socket);
            m_logger.Log("Connection accepted.");

            bool connection = true;

            while (connection) {
                try {
                    int rc = modbus_receive(m_modbus, m_query);
                    if (rc > 0) {
                        if (m_query[header_length] == 5 || m_query[header_length] == 6) {
                            // write (single) coil or register
                            uint8_t message[5];
                            for (int i = header_length; i < rc; i++) {
                                message[i - header_length] = m_query[i];
                            }
                            m_messageHandler.handleMessage(message);
                        } else if (m_query[header_length] == 16) {
                            // write multiple registers, starting from 22
                            if (m_query[header_length + 2] == 22) {
                                int count = m_query[header_length + 4];
                                auto values = Configurations::load();
                                for (int j = 0, index = header_length + 6; j < count; j++, index+=2) {
                                    values[j] = m_query[index + 1] | m_query[index] << 8;
                                }
                                onConfigurations(values);
                            }
                        }
                        modbus_reply(m_modbus, m_query, rc, m_mapping);
                    } else if (rc == -1) {
                        m_logger.Log("Connection stopped.");
                        connection = false;
                    }
                } catch (std::exception &e) {
                    m_logger.Log(e.what());
                }
            }
        }
    }
}

void ModbusThread::receiveState(bool state)
{
    m_mapping->tab_input_bits[0] = state;
    m_mapping->tab_bits[0] = state;
}

void ModbusThread::receiveCount(int tempoComponent, int count, double percentage)
{
    int capacityIndex = (tempoComponent * 3) + 4;
    int percentageIndex = capacityIndex + 1;
    int countIndex = percentageIndex + 1;

    m_mapping->tab_input_registers[percentageIndex] = std::round(percentage * 100);
    m_mapping->tab_input_registers[countIndex] = count;
}

void ModbusThread::receiveRate(int rate)
{
    m_mapping->tab_input_registers[3] = rate;
}

void ModbusThread::receiveConfigurations(std::vector<int> values)
{
    for (int i = 22; i <= 28; i++) {
        m_mapping->tab_registers[i] = values[i - 22];
    }
}

void ModbusThread::onReceiveConfigurations(std::function<void (std::vector<int>)> callback)
{
    onConfigurations = callback;
}
