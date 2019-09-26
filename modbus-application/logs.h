#ifndef LOGS_H
#define LOGS_H

#include "bittogglethread.h"
#include "modbusthread.h"
#include "simulator.h"

#include <QFrame>

namespace Ui {
class Logs;
}

class Logs : public QFrame
{
    Q_OBJECT
    Simulator& simulator;
    std::shared_ptr<ExternalMachineMessageReceiver> listener;
    QString convertType(ComponentMessageType type);
    modbus_mapping_t * mappings;
    BitToggleThread * toggle;
    Ui::Logs *ui;
public:
    Logs(Simulator& simulator, modbus_mapping_t * mappings, QWidget *parent = nullptr);
    ~Logs();
    Q_INVOKABLE void createAlarmPopup(QString, QWidget*, QWidget*);

    class LogsMessageReceiver : public ExternalMachineMessageReceiver {
    private:
        Logs& logs;
    public:
        LogsMessageReceiver(Logs&);
        void ReceiveMessage(std::shared_ptr<ComponentMessage>) override;
    };
};

#endif // LOGS_H
