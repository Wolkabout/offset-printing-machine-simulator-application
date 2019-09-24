#include "modbusthread_listeners.h"

#include <QObject>

ModbusMachineStateListener::ModbusMachineStateListener(ModbusThread& thread) : thread(thread) {
    QObject::connect(this, SIGNAL(setState(bool)), &thread, SLOT(receiveState(bool)), Qt::ConnectionType::QueuedConnection);
}

void ModbusMachineStateListener::ReceiveMachineState(bool state) {
    emit setState(state);
}

ModbusCountListener::ModbusCountListener(ModbusThread& thread, int componentIndex) : thread(thread) {
    this->componentIndex = componentIndex;
    QObject::connect(this, SIGNAL(setCount(int, int, double)), &thread, SLOT(receiveState(int, int, double)), Qt::ConnectionType::QueuedConnection);
}

void ModbusCountListener::ReceiveMessage(std::shared_ptr<CountMessage> message) {
    if (message->getCount() % 10 == 0)
        emit setCount(componentIndex, message->getCount(), message->getPercentage());
}

ModbusRateListener::ModbusRateListener(ModbusThread& thread) : thread(thread) {
    QObject::connect(this, SIGNAL(setRate(int)), &thread, SLOT(receiveRate(int)), Qt::ConnectionType::QueuedConnection);
}

void ModbusRateListener::ReceiveMessage(std::shared_ptr<ConveyorRateMessage> message) {
    emit setRate(message->getCurrentRate());
}
