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
#include "configurations.h"

class ModbusThread : public QThread
{
private:
    Q_OBJECT
    modbus_t * modbus;
    modbus_mapping_t * mapping;
    bool shouldListen;
    std::function<void()> breaker;
    uint8_t * query;
    QString addressString;
    Logger logger;
    Simulator& simulator;
    ModbusThreadMessageHandler messageHandler;

    std::shared_ptr<ExternalMachineStateReceiver> stateListener;
    std::shared_ptr<CountMessageReceiver> feederListener; // 0
    std::shared_ptr<CountMessageReceiver> deliveryListener; // 1
    std::shared_ptr<CountMessageReceiver> cyanListener; // 2
    std::shared_ptr<CountMessageReceiver> magentaListener; // 3
    std::shared_ptr<CountMessageReceiver> yellowListener; // 4
    std::shared_ptr<CountMessageReceiver> blackListener; // 5
    std::shared_ptr<ConveyorRateMessageReceiver> conveyorListener;

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
