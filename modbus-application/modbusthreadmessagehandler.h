#ifndef MODBUSTHREADMESSAGEHANDLER_H
#define MODBUSTHREADMESSAGEHANDLER_H

#include "simulator.h"
#include "modbus/modbus.h"

class ModbusThreadMessageHandler
{
    modbus_mapping_t * mappings;
    Simulator& simulator;
public:
    ModbusThreadMessageHandler(modbus_mapping_t *, Simulator&);
    void handleMessage(uint8_t message[]);
};

#endif // MODBUSTHREADMESSAGEHANDLER_H
