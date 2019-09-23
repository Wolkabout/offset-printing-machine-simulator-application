#ifndef MODBUSTHREAD_H
#define MODBUSTHREAD_H

#include <QThread>
#include <iostream>
#include <modbus/modbus.h>

class ModbusThread : public QThread
{
private:
    Q_OBJECT
    modbus_t * modbus;
    modbus_mapping_t * mapping;
    uint8_t * query;
    QString addressString;

    void run() override;
    void printMappings();

public:
    ModbusThread();
    ~ModbusThread();
    modbus_mapping_t *getMapping() const;
};

#endif // MODBUSTHREAD_H
