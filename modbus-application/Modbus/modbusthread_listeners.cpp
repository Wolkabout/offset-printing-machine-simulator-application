#include "modbusthread_listeners.h"

#include <QObject>

ModbusMachineStateListener::ModbusMachineStateListener(ModbusThread& thread) : m_thread(thread) {
    QObject::connect(this, SIGNAL(setState(bool)), &m_thread, SLOT(receiveState(bool)), Qt::ConnectionType::QueuedConnection);
}

void ModbusMachineStateListener::ReceiveMachineState(bool state) {
    emit setState(state);
}

ModbusCountListener::ModbusCountListener(ModbusThread& thread, int componentIndex) :
    m_thread(thread), m_componentIndex(componentIndex) {
    QObject::connect(this, SIGNAL(setCount(int, int, double)), &m_thread, SLOT(receiveCount(int, int, double)), Qt::ConnectionType::QueuedConnection);
}

void ModbusCountListener::ReceiveMessage(std::shared_ptr<CountMessage> message) {
    if (message->getCount() % 10 == 0)
        emit setCount(m_componentIndex, message->getCount(), message->getPercentage());
}

ModbusRateListener::ModbusRateListener(ModbusThread& thread) : m_thread(thread) {
    QObject::connect(this, SIGNAL(setRate(int)), &m_thread, SLOT(receiveRate(int)), Qt::ConnectionType::QueuedConnection);
}

void ModbusRateListener::ReceiveMessage(std::shared_ptr<ConveyorRateMessage> message) {
    emit setRate(message->getCurrentRate());
}
