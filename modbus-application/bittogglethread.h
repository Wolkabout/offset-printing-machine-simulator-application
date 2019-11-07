#ifndef BITTOGGLETHREAD_H
#define BITTOGGLETHREAD_H

#include "modbusthread.h"

#include <QThread>

class BitToggleThread : public QThread {
    Q_OBJECT
    modbus_mapping_t * mappings;
    int bit;
public:
    BitToggleThread(int bit, modbus_mapping_t * mappings) {
        this->bit = bit;
        this->mappings = mappings;
    }
    void run() override {
        mappings->tab_input_registers[bit] = 1;
        std::this_thread::sleep_for(std::chrono::seconds(5));
        mappings->tab_input_registers[bit] = 0;
        finished();
    }
};

#endif // BITTOGGLETHREAD_H
