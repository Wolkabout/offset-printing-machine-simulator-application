#ifndef MODBUSTHREADMESSAGEHANDLER_H
#define MODBUSTHREADMESSAGEHANDLER_H

#include "simulator.h"

class ModbusThreadMessageHandler
{
    Simulator& simulator;
public:
    ModbusThreadMessageHandler(Simulator&);
    void handleMessage(uint8_t message[]);
};

#endif // MODBUSTHREADMESSAGEHANDLER_H
