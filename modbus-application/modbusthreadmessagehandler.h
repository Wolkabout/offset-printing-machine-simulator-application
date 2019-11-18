#ifndef MODBUSTHREADMESSAGEHANDLER_H
#define MODBUSTHREADMESSAGEHANDLER_H

#include "simulator.h"
#include "modbus/modbus.h"

class ModbusThreadMessageHandler
{
    modbus_mapping_t * mappings;
    Simulator& simulator;
    std::function<void(std::vector<int>)> callback;
public:
    ModbusThreadMessageHandler(modbus_mapping_t *, Simulator&);
    void handleMessage(uint8_t message[]);
    void setCallback(std::function<void(std::vector<int>)>);
};

#endif // MODBUSTHREADMESSAGEHANDLER_H
