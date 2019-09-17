#include "logs.h"
#include "ui_logs.h"
#include <QTime>

Logs::Logs(Simulator& simulator, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Logs),
    simulator(simulator)
{
    ui->setupUi(this);

    listener = std::make_shared<LogsMessageReceiver>(*this);
    simulator.getMachine()->getExternalMessageReceivers().push_back(listener);
}

Logs::LogsMessageReceiver::LogsMessageReceiver(Logs& logs) : logs(logs) { }

void Logs::LogsMessageReceiver::ReceiveMessage(std::shared_ptr<ComponentMessage> message)
{
    auto timestamp = QTime::currentTime().toString("hh:mm:ss.zzz");
    logs.ui->logs->appendPlainText("[" + timestamp + "] -> " + message->getType() + " | " + QString::fromStdString(message->getContent()));
}

Logs::~Logs()
{
    delete ui;
}
