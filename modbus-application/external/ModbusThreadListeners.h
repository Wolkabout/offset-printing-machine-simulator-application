#ifndef MODBUSTHREAD_LISTENERS_H
#define MODBUSTHREAD_LISTENERS_H

#include "ModbusThread.h"

class ModbusMachineStateListener : public QObject, public simulator::ExternalMachineStateReceiver
{
    Q_OBJECT
public:
    ModbusMachineStateListener(const ModbusThread&);

    void ReceiveMachineState(bool) override;

signals:
    void setState(bool);

private:
    const ModbusThread& m_thread;
};

class ModbusCountListener : public QObject, public simulator::CountMessageReceiver
{
    Q_OBJECT
public:
    ModbusCountListener(const ModbusThread&, int);

    void ReceiveMessage(std::shared_ptr<simulator::CountMessage>) override;

signals:
    void setCount(int, int, double);

private:
    const ModbusThread& m_thread;
    int m_componentIndex;
};

class ModbusRateListener : public QObject, public simulator::ConveyorRateMessageReceiver
{
    Q_OBJECT
public:
    ModbusRateListener(const ModbusThread&);

    void ReceiveMessage(std::shared_ptr<simulator::ConveyorRateMessage>) override;

signals:
    void setRate(int);

private:
    const ModbusThread& m_thread;
};

#endif // MODBUSTHREAD_LISTENERS_H
