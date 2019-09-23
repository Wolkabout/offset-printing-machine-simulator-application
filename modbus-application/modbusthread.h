#ifndef MODBUSTHREAD_H
#define MODBUSTHREAD_H

#include <QThread>
#include <modbus/modbus.h>

class ModbusThread : public QThread
{
private:
    Q_OBJECT
    modbus_t * modbus;
    modbus_mapping_t * mapping;
    void run() {
        int listen = modbus_tcp_listen(modbus, 1);
        qDebug((std::string("START : ") + std::to_string(listen)).c_str());
        sleep(2);

        while (true) {
//            attempt to find client
            qDebug((std::string("TCP_ACCEPT ") + std::to_string(modbus_tcp_accept(modbus, &listen))).c_str());
            qDebug((std::string("LISTEN ") + std::to_string(listen)).c_str());

            sleep(1);

//            if the connection is successful
//            while (true) {
//                uint8_t query[MODBUS_TCP_MAX_ADU_LENGTH];
//                int rc;

//                rc = modbus_receive(modbus, query);
//                if (rc > 0) {
//                    /* rc is the query size */
//                    modbus_reply(modbus, query, rc, mapping);
//                } else if (rc == -1) {
//                    break;
//                }
//            }
        }
    }
public:
    ModbusThread(modbus_t * modbus, modbus_mapping_t * mappping) {
        this->modbus = modbus;
        this->mapping = mapping;
    }
};

#endif // MODBUSTHREAD_H
