#ifndef BITTOGGLETHREAD_H
#define BITTOGGLETHREAD_H

#include "Modbus/modbusthread.h"

#include <QThread>

class BitToggleThread : public QThread {
    Q_OBJECT
    modbus_mapping_t * m_mappings;
    int m_bit;
public:
    BitToggleThread(int bit, modbus_mapping_t * mappings) : m_mappings(mappings), m_bit(bit) {}
    void run() override {
//        qDebug("Starting thread for bit %i (prev. value %i, setting to %i)", bit, mappings->tab_input_registers[bit], 1);
        m_mappings->tab_input_bits[m_bit] = 1;
        std::this_thread::sleep_for(std::chrono::seconds(5));
//        qDebug("Stopping thread for bit %i (prev. value %i, setting to %i)", bit, mappings->tab_input_registers[bit], 0);
        m_mappings->tab_input_bits[m_bit] = 0;
        finished();
    }
};

#endif // BITTOGGLETHREAD_H
