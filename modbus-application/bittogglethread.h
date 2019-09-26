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
        qDebug("Invoked! %i", bit);
        mappings->tab_bits[bit] = true;
        std::this_thread::sleep_for(std::chrono::seconds(10));
        mappings->tab_bits[bit] = false;
    }
};

#endif // BITTOGGLETHREAD_H
