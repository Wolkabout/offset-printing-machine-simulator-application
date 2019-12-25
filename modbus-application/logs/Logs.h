#ifndef LOGS_H
#define LOGS_H

#include "external/BitToggleThread.h"
#include "external/ModbusThread.h"
#include "Simulator.h"

#include <QFrame>

namespace Ui
{
    class Logs;
}

class Logs : public QFrame
{
    Q_OBJECT

public:
    Logs(const Simulator& simulator, modbus_mapping_t *mappings, QWidget *parent = nullptr);

    ~Logs();

    Q_INVOKABLE void createAlarmPopup(QString, QWidget *, QWidget *);

    class LogsMessageReceiver : public simulator::ExternalMachineMessageReceiver
    {
    public:
        LogsMessageReceiver(Logs&);

        void ReceiveMessage(std::shared_ptr<simulator::ComponentMessage>) override;

    private:
        Logs& m_logs;
    };

private:
    QString convertType(simulator::ComponentMessageType type);

    const Simulator& m_simulator;
    std::shared_ptr<simulator::ExternalMachineMessageReceiver> m_listener;
    modbus_mapping_t *m_mappings;
    BitToggleThread *m_toggle;
    Ui::Logs *ui;
};

#endif // LOGS_H
