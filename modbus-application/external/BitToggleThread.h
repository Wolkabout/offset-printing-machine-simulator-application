#ifndef BITTOGGLETHREAD_H
#define BITTOGGLETHREAD_H

#include "modbus/modbus.h"

#include <thread>
#include <QThread>

class BitToggleThread : public QThread
{
    Q_OBJECT
public:
    BitToggleThread(int bit, modbus_mapping_t *mappings) : m_mappings(mappings), m_bit(bit) {}

    void run() override
    {
        m_mappings->tab_input_bits[m_bit] = 1;
        std::this_thread::sleep_for(std::chrono::seconds(5));
        m_mappings->tab_input_bits[m_bit] = 0;
        finished();
    }
private:
    modbus_mapping_t *m_mappings;
    int m_bit;
};

#endif // BITTOGGLETHREAD_H
