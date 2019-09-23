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
        if (listen < 1) {
            qDebug("The program doesn\'t have permissions to run modbus server.");
            return;
        }

        while (true) {
//            this line is blocking! if there's no connection, it won't continue from here!
            modbus_tcp_accept(modbus, &listen);
            qDebug(std::string("ACCEPT " + std::to_string(listen)).c_str());
            sleep(1);

//            if the connection is successful
            while (true) {
                try {
                    uint8_t query[MODBUS_TCP_MAX_ADU_LENGTH];
                    int rc;
                    rc = modbus_receive(modbus, query);
                    if (rc > 0) {
                        modbus_reply(modbus, query, rc, mapping);
                    } else if (rc == -1) {
                        break;
                    }
                } catch (std::exception &e) {
                    qDebug(e.what());
                }
            }
        }
    }
public:
    ModbusThread(modbus_t * modbus, modbus_mapping_t * mappping) {
        this->modbus = modbus;
        this->mapping = mapping;
    }
};

#endif // MODBUSTHREAD_H
