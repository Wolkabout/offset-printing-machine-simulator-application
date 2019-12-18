#ifndef MODBUSTHREAD_LISTENERS_H
#define MODBUSTHREAD_LISTENERS_H

#include "modbusthread.h"

class ModbusMachineStateListener : public QObject, public ExternalMachineStateReceiver {
    Q_OBJECT
    ModbusThread& m_thread;
public:
    ModbusMachineStateListener(ModbusThread&);
    void ReceiveMachineState(bool) override;
signals:
    void setState(bool);
};

class ModbusCountListener : public QObject, public CountMessageReceiver {
    Q_OBJECT
    ModbusThread& m_thread;
    int m_componentIndex;
public:
    ModbusCountListener(ModbusThread&, int);
    void ReceiveMessage(std::shared_ptr<CountMessage>) override;
signals:
    void setCount(int, int, double);
};

class ModbusRateListener : public QObject, public ConveyorRateMessageReceiver {
    Q_OBJECT
    ModbusThread& m_thread;
public:
    ModbusRateListener(ModbusThread&);
    void ReceiveMessage(std::shared_ptr<ConveyorRateMessage>) override;
signals:
    void setRate(int);
};

#endif // MODBUSTHREAD_LISTENERS_H
