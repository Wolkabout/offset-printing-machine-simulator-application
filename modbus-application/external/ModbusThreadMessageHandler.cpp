#include "ModbusThreadMessageHandler.h"
#include "settings/Configurations.h"

ModbusThreadMessageHandler::ModbusThreadMessageHandler(modbus_mapping_t *mappings, const Simulator& simulator) :
        m_mappings(mappings),
        m_simulator(simulator),
        m_callback(nullptr) {}

void ModbusThreadMessageHandler::handleMessage(uint8_t message[])
{
    int registerIndex = message[2] | message[1] << 8;
    int value = message[4] | message[3] << 8;

    qDebug("%i %i", registerIndex, value);
    if (message[0] == 5 && registerIndex == 0)
    {
        if (value != 0)
        {
            m_simulator.getMachine()->start();
        }
        else
        {
            m_simulator.getMachine()->stop();
        }
    }
    else if (message[0] == 6)
    {
        if (registerIndex == 3)
        {
            m_simulator.getConveyor()->setRatePerHour(value);
            return;
        }

        switch (registerIndex)
        {
            case 6:
                m_simulator.getFeeder()->modifyCount(value);
                break;
            case 9:
                m_simulator.getDelivery()->modifyCount(value);
                break;
            case 12:
                m_simulator.getCyanPaint()->modifyCount(value);
                break;
            case 15:
                m_simulator.getMagentaPaint()->modifyCount(value);
                break;
            case 18:
                m_simulator.getYellowPaint()->modifyCount(value);
                break;
            case 21:
                m_simulator.getBlackPaint()->modifyCount(value);
                break;
            case 25:
            case 26:
            case 27:
            case 28:
                qDebug("Setting configuration value : %i %i", registerIndex, value);
                auto values = Configurations::load();
                values[registerIndex % 22] = value;
                if (m_callback != nullptr)
                {
                    m_callback(values);
                }
                break;
        }
    }
}

void ModbusThreadMessageHandler::setCallback(std::function<void(std::vector<int>)> callback)
{
    this->m_callback = callback;
}
