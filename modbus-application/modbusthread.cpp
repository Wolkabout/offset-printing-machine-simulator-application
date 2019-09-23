#include "modbusthread.h"
#include "utility.h"

ModbusThread::ModbusThread()
{
    addressString = Utility::getIp();
    modbus = modbus_new_tcp(addressString.toStdString().c_str(), 2222);
    modbus_set_debug(modbus, TRUE);
    modbus_set_response_timeout(modbus, 60, 0);

    mapping = modbus_mapping_new(30, 30, 30, 30);
    if (mapping == nullptr) {
        qDebug("The mapping couldn\'t be allocated!");
        this->~ModbusThread();
        return;
    }

//    printMappings();
}

ModbusThread::~ModbusThread() {
    terminate();
    if (mapping != nullptr)
        modbus_mapping_free(mapping);
    modbus_close(modbus);
    modbus_free(modbus);
}


modbus_mapping_t *ModbusThread::getMapping() const
{
    return mapping;
}

void ModbusThread::run() {
    int listen = modbus_tcp_listen(modbus, 1);
    if (listen < 1) {
        qDebug("The program doesn\'t have permissions to run modbus server.");
        return;
    }

    int header_length = modbus_get_header_length(modbus);
    query = new uint8_t[MODBUS_TCP_MAX_ADU_LENGTH] () ;

    while (true) {
//            this line is blocking! if there's no connection, it won't continue from here until one shows up!
        modbus_tcp_accept(modbus, &listen);
        sleep(1);

//            if the connection is successful
        while (true) {
            try {
                int rc;
                rc = modbus_receive(modbus, query);
//                qDebug("%i", rc);
//                for (int i = header_length; i < rc; i++) {
//                    qDebug("%i", query[i]);
//                }
                if (rc > 0) {
//                    printMappings();
//                    if (query[header_length] == 3) {
//                        qDebug("Reading multiple holding registers!");
//                        // WHY AM I GETTING 36168 here?
//                        int index = query[header_length + 1] | query[header_length + 2] << 8;
//                        qDebug("%i", index);
//                        qDebug("%i", mapping->tab_registers[index]);
//                    }
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

void ModbusThread::printMappings() {
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
