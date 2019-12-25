#ifndef MODBUSTHREADMESSAGEHANDLER_H
#define MODBUSTHREADMESSAGEHANDLER_H

#include "modbus/modbus.h"
#include "Simulator.h"

class ModbusThreadMessageHandler
{
public:
    ModbusThreadMessageHandler(modbus_mapping_t *, const Simulator&);

    void handleMessage(uint8_t message[]);

    void setCallback(std::function<void(std::vector<int>)>);
private:
    modbus_mapping_t *m_mappings;
    const Simulator& m_simulator;
    std::function<void(std::vector<int>)> m_callback;
};

#endif // MODBUSTHREADMESSAGEHANDLER_H
