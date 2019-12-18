#ifndef MODBUSTHREADMESSAGEHANDLER_H
#define MODBUSTHREADMESSAGEHANDLER_H

#include "simulator.h"
#include "modbus/modbus.h"

class ModbusThreadMessageHandler
{
    modbus_mapping_t * m_mappings;
    Simulator& m_simulator;
    std::function<void(std::vector<int>)> m_callback;
public:
    ModbusThreadMessageHandler(modbus_mapping_t *, Simulator&);
    void handleMessage(uint8_t message[]);
    void setCallback(std::function<void(std::vector<int>)>);
};

#endif // MODBUSTHREADMESSAGEHANDLER_H
