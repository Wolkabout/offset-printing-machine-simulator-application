#include "modbusthreadmessagehandler.h"

ModbusThreadMessageHandler::ModbusThreadMessageHandler(Simulator& simulator) : simulator(simulator) { }

void ModbusThreadMessageHandler::handleMessage(uint8_t message[])
{
    int registerIndex = message[2] | message[1] << 8;
    int value = message[4] | message[3] << 8;

    if (message[0] == 5) {
        if (registerIndex == 0) {
            if (value != 0) {
                // turn on machine
            }
            else {
                // turn off machine
            }
        }
    } else if (message[0] == 6) {
        if (registerIndex == 3) {
            // set conveyor rate
        }
        else {
            registerIndex -= 6;
            registerIndex /= 3;
            // modify count
        }
    }
}


