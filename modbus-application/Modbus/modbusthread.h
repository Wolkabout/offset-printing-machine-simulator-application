#ifndef MODBUSTHREAD_H
#define MODBUSTHREAD_H

#include "modbusthreadmessagehandler.h"
#include "simulator.h"
#include <Interfaces/ConveyorRateMessageReceiver.h>
#include <Interfaces/CountMessageReceiver.h>
#include <Interfaces/ExternalMachineStateReceiver.h>
#include <Logger/Logger.h>
#include <QThread>
#include <iostream>
#include <modbus/modbus.h>
#include "Settings/configurations.h"

class ModbusThread : public QThread
{
private:
    Q_OBJECT
    modbus_t * m_modbus;
    modbus_mapping_t * m_mapping;
    bool m_shouldListen;
    std::function<void()> m_breaker;
    uint8_t * m_query;
    QString m_addressString;
    Logger m_logger;
    Simulator& m_simulator;
    ModbusThreadMessageHandler m_messageHandler;

    std::shared_ptr<ExternalMachineStateReceiver> m_stateListener;
    std::shared_ptr<CountMessageReceiver> m_feederListener; // 0
    std::shared_ptr<CountMessageReceiver> m_deliveryListener; // 1
    std::shared_ptr<CountMessageReceiver> m_cyanListener; // 2
    std::shared_ptr<CountMessageReceiver> m_magentaListener; // 3
    std::shared_ptr<CountMessageReceiver> m_yellowListener; // 4
    std::shared_ptr<CountMessageReceiver> m_blackListener; // 5
    std::shared_ptr<ConveyorRateMessageReceiver> m_conveyorListener;

    void run() override;
    void printMappings();

public:
    ModbusThread(Simulator&);
    ~ModbusThread();
    std::function<void(std::vector<int>)> onConfigurations;

    modbus_mapping_t *getMapping() const;
    Q_INVOKABLE void receiveState(bool);
    Q_INVOKABLE void receiveCount(int, int, double);
    Q_INVOKABLE void receiveRate(int);
    void receiveConfigurations(std::vector<int> values);
    void onReceiveConfigurations(std::function<void(std::vector<int>)>);
};

#endif // MODBUSTHREAD_H
