#ifndef BITTOGGLETHREAD_H
#define BITTOGGLETHREAD_H

#include "Modbus/modbusthread.h"

#include <QThread>

class BitToggleThread : public QThread {
    Q_OBJECT
    modbus_mapping_t * mappings;
    int bit;
public:
    BitToggleThread(int bit, modbus_mapping_t * mappings) {
        this->bit = bit;
        this->mappings = mappings;
//        qDebug("Created thread for bit %i", bit);
    }
    void run() override {
//        qDebug("Starting thread for bit %i (prev. value %i, setting to %i)", bit, mappings->tab_input_registers[bit], 1);
        mappings->tab_input_bits[bit] = 1;
        std::this_thread::sleep_for(std::chrono::seconds(5));
//        qDebug("Stopping thread for bit %i (prev. value %i, setting to %i)", bit, mappings->tab_input_registers[bit], 0);
        mappings->tab_input_bits[bit] = 0;
        finished();
    }
};

#endif // BITTOGGLETHREAD_H
