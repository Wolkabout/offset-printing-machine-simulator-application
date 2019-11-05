#include "alarmalert.h"
#include "bittogglethread.h"
#include "logs.h"
#include "ui_logs.h"
#include <QMessageBox>
#include <QTime>

QString Logs::convertType(ComponentMessageType type)
{
    switch (type) {
        case Neutral: return "Neutral";
        case Alarming: return "Alarming";
        case Severe: return "Severe";
    }
}

Logs::Logs(Simulator& simulator, modbus_mapping_t * mappings, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Logs),
    simulator(simulator)
{
    ui->setupUi(this);
    this->mappings = mappings;

    QFont robotoMedium14(QFontDatabase::applicationFontFamilies(0).at(0), 10, QFont::DemiBold);
    ui->logs->setFont(robotoMedium14);

    auto timestamp = QTime::currentTime().toString("hh:mm:ss.zzz");
    for (auto &message : simulator.getMachine()->getMessages()) {
        ui->logs->appendPlainText("[" + timestamp + "] -> " + convertType(message->getType()) + " | " + QString::fromStdString(message->getContent()) + '\n');
        if (message->getType() == Severe) {
            createAlarmPopup(QString::fromStdString(message->getContent()), nullptr, nullptr);
        }
    }

    mappings->tab_input_registers[24] = 0;
    mappings->tab_input_registers[25] = 0;

    listener = std::make_shared<LogsMessageReceiver>(*this);
    simulator.getMachine()->getExternalMessageReceivers().push_back(listener);
}

void Logs::createAlarmPopup(QString message, QWidget *component, QWidget *parent)
{
    AlarmAlert * aa = new AlarmAlert(message, simulator, component, parent);
    aa->show();

    if (message == "The Emergency Button was triggered!") {
        toggle = new BitToggleThread(24, mappings);
        toggle->start();
    }
    else if (message == "A paper jammed the machine!") {
        toggle = new BitToggleThread(25, mappings);
        toggle->start();
    }
}

Logs::LogsMessageReceiver::LogsMessageReceiver(Logs& logs) : logs(logs) { }

void Logs::LogsMessageReceiver::ReceiveMessage(std::shared_ptr<ComponentMessage> message)
{
    auto timestamp = QTime::currentTime().toString("hh:mm:ss.zzz");
    logs.ui->logs->appendPlainText("[" + timestamp + "] -> " + logs.convertType(message->getType()) + " | " + QString::fromStdString(message->getContent()) + '\n');
    // Now we invoke for everything, not just severe alerts
    QMetaObject::invokeMethod(&logs, "createAlarmPopup", Qt::QueuedConnection, Q_ARG(QString, QString::fromStdString(message->getContent())), Q_ARG(QWidget*, nullptr), Q_ARG(QWidget*, nullptr));
}

Logs::~Logs()
{
    delete ui;
}
