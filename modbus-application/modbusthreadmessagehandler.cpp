#include "modbusthreadmessagehandler.h"

ModbusThreadMessageHandler::ModbusThreadMessageHandler(modbus_mapping_t * mappings, Simulator& simulator) : simulator(simulator) {
    this->mappings = mappings;
}

void ModbusThreadMessageHandler::handleMessage(uint8_t message[])
{
    int registerIndex = message[2] | message[1] << 8;
    int value = message[4] | message[3] << 8;

    qDebug("%i %i", registerIndex, value);
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
                simulator.getFeeder()->modifyCount(value);
                break;
                case 9:
                simulator.getDelivery()->modifyCount(value);
                break;
                case 12:
                simulator.getCyanPaint()->modifyCount(value);
                break;
                case 15:
                simulator.getMagentaPaint()->modifyCount(value);
                break;
                case 18:
                simulator.getYellowPaint()->modifyCount(value);
                break;
                case 21:
                simulator.getBlackPaint()->modifyCount(value);
                break;
            }
        }
    }
}


