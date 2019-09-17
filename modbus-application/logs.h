#ifndef LOGS_H
#define LOGS_H

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
public:
    Logs(Simulator& simulator, QWidget *parent = nullptr);
    ~Logs();

private:
    Ui::Logs *ui;
    class LogsMessageReceiver : public ExternalMachineMessageReceiver {
    private:
        Logs& logs;
    public:
        LogsMessageReceiver(Logs&);
        void ReceiveMessage(std::shared_ptr<ComponentMessage>) override;
    };
};

#endif // LOGS_H
