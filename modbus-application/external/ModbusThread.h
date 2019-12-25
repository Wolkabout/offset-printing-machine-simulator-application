#ifndef MODBUSTHREAD_H
#define MODBUSTHREAD_H

#include "interfaces/ConveyorRateMessageReceiver.h"
#include "interfaces/CountMessageReceiver.h"
#include "interfaces/ExternalMachineStateReceiver.h"
#include "logger/Logger.h"
#include "ModbusThreadMessageHandler.h"
#include "modbus/modbus.h"
#include "settings/Configurations.h"
#include "Simulator.h"

#include <QThread>

class ModbusThread : public QThread
{
    Q_OBJECT

public:
    ModbusThread(const Simulator&);

    ~ModbusThread();

    std::function<void(std::vector<int>)> onConfigurations;

    modbus_mapping_t *getMapping() const;

    void receiveConfigurations(std::vector<int> values);

    void onReceiveConfigurations(std::function<void(std::vector<int>)>);

    Q_INVOKABLE void receiveState(bool);

    Q_INVOKABLE void receiveCount(int, int, double);

    Q_INVOKABLE void receiveRate(int);

private:

    void printMappings();

    void run() override;

    modbus_t *m_modbus;
    modbus_mapping_t *m_mapping;
    bool m_shouldListen;
    std::function<void()> m_breaker;
    uint8_t *m_query;
    QString m_addressString;
    simulator::Logger m_logger;
    const Simulator& m_simulator;
    ModbusThreadMessageHandler m_messageHandler;

    std::shared_ptr<simulator::ExternalMachineStateReceiver> m_stateListener;
    std::shared_ptr<simulator::CountMessageReceiver> m_feederListener; // 0
    std::shared_ptr<simulator::CountMessageReceiver> m_deliveryListener; // 1
    std::shared_ptr<simulator::CountMessageReceiver> m_cyanListener; // 2
    std::shared_ptr<simulator::CountMessageReceiver> m_magentaListener; // 3
    std::shared_ptr<simulator::CountMessageReceiver> m_yellowListener; // 4
    std::shared_ptr<simulator::CountMessageReceiver> m_blackListener; // 5
    std::shared_ptr<simulator::ConveyorRateMessageReceiver> m_conveyorListener;
};

#endif // MODBUSTHREAD_H
