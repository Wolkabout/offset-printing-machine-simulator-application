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
        mapping = modbus_mapping_new(30, 30, 30, 30);
        printMappings();

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
                        printMappings();
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
    void printMappings() {
        try {
            qDebug("tab_bits | starting at %#x", mapping->tab_bits);
            for (int i = 0; i < 30; i++)
                qDebug("%#x %u", (mapping->tab_bits + (sizeof(uint8_t) * i)), mapping->tab_bits[i]);

            qDebug("tab_input_bits | starting at %#x", mapping->tab_input_bits);
            for (int i = 0; i < 30; i++)
                qDebug("%#x %u", (mapping->tab_input_bits + (sizeof(uint8_t) * i)), mapping->tab_input_bits[i]);

            qDebug("tab_registers | starting at %#x", mapping->tab_registers);
            for (int i = 0; i < 30; i++)
                qDebug("%#x %u", (mapping->tab_registers + (sizeof(uint16_t) * i)), mapping->tab_registers[i]);

            qDebug("tab_input_registers | %#x", mapping->tab_input_registers);
            for (int i = 0; i < 30; i++)
                qDebug("%#x %u", (mapping->tab_input_registers + (sizeof(uint16_t) * i)), mapping->tab_input_registers[i]);
        } catch (std::exception &e) {
            qDebug("%s", e.what());
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
