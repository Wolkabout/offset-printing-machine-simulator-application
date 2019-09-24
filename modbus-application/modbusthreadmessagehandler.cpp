#include "modbusthreadmessagehandler.h"

ModbusThreadMessageHandler::ModbusThreadMessageHandler(modbus_mapping_t * mappings, Simulator& simulator) : simulator(simulator) {
    this->mappings = mappings;
}

void ModbusThreadMessageHandler::handleMessage(uint8_t message[])
{
    int registerIndex = message[2] | message[1] << 8;
    int value = message[4] | message[3] << 8;

    if (message[0] == 5) {
        if (registerIndex == 0) {
            if (value != 0) {
                simulator.getMachine()->start();
            }
            else {
                simulator.getMachine()->stop();
            }
        }
    } else if (message[0] == 6) {
        if (registerIndex == 3) {
            simulator.getConveyor()->setRatePerHour(value);
        }
        else {
            switch (registerIndex) {
                case 6:
                if (simulator.getFeeder()->modifyCount(value)) {
                    mappings->tab_registers[registerIndex] = 0;
                }
                break;
                case 9:
                if (simulator.getDelivery()->modifyCount(value)) {
                    mappings->tab_registers[registerIndex] = 0;
                }
                break;
                case 12:
                if (simulator.getCyanPaint()->modifyCount(value)) {
                    mappings->tab_registers[registerIndex] = 0;
                }
                break;
                case 15:
                if (simulator.getMagentaPaint()->modifyCount(value)) {
                    mappings->tab_registers[registerIndex] = 0;
                }
                break;
                case 18:
                if (simulator.getYellowPaint()->modifyCount(value)) {
                    mappings->tab_registers[registerIndex] = 0;
                }
                break;
                case 21:
                if (simulator.getBlackPaint()->modifyCount(value)) {
                    mappings->tab_registers[registerIndex] = 0;
                }
                break;
            }
        }
    }
}


