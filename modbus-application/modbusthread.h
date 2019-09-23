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
    void run() {
        int listen = modbus_tcp_listen(modbus, 1);
        if (listen < 1) {
            qDebug("The program doesn\'t have permissions to run modbus server.");
            return;
        }

        int header_length = modbus_get_header_length(modbus);
        qDebug(std::string("HEADER_LENGTH : " + std::to_string(header_length)).c_str());

        while (true) {
//            this line is blocking! if there's no connection, it won't continue from here until one shows up!
            modbus_tcp_accept(modbus, &listen);
//            qDebug(std::string("ACCEPT " + std::to_string(listen)).c_str());
            sleep(1);
            query = new uint8_t[MODBUS_TCP_MAX_ADU_LENGTH] () ;

//            if the connection is successful
            while (true) {
                try {
                    int rc;
                    rc = modbus_receive(modbus, query);
                    qDebug("%i", rc);
                    for (int i = header_length; i < rc; i++) {
                        qDebug("%i", query[i]);
                    }
                    if (rc > 0) {
                        if (query[header_length] == 3) {
                            qDebug("Reading multiple holding registers!");
                            // WHY AM I GETTING 36168 here?
                            int index = query[header_length + 1] | query[header_length + 2] << 8;
                            qDebug("%i", index);
                            qDebug("%i", mapping->tab_registers[index]);
                        }
                        modbus_reply(modbus, query, rc, mapping);
                    } else if (rc == -1) {
                        break;
                    }
                } catch (std::exception &e) {
                    qDebug(e.what());
                }
            }

            delete query;
        }
    }
public:
    ModbusThread(modbus_t * modbus, modbus_mapping_t * mappping)
    {
        this->modbus = modbus;
        this->mapping = mapping;
    }
};

#endif // MODBUSTHREAD_H
