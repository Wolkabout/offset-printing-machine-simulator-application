#include "AlarmAlert.h"
#include "external/BitToggleThread.h"
#include "Logs.h"
#include "ui_Logs.h"

#include <QTime>

QString Logs::convertType(simulator::ComponentMessageType type)
{
    switch (type)
    {
        case simulator::ComponentMessageType::NEUTRAL:
            return "Neutral";
        case simulator::ComponentMessageType::ALARMING:
            return "Alarming";
        case simulator::ComponentMessageType::SEVERE:
            return "Severe";
    }
    return "";
}

Logs::Logs(const Simulator& simulator, modbus_mapping_t *mappings, QWidget *parent) :
        QFrame(parent),
        m_simulator(simulator),
        m_mappings(mappings),
        ui(new Ui::Logs)
{
    ui->setupUi(this);

    QFont robotoMedium14(QFontDatabase::applicationFontFamilies(0).at(0), 10, QFont::DemiBold);
    ui->logs->setFont(robotoMedium14);

    auto timestamp = QTime::currentTime().toString("hh:mm:ss.zzz");
    for (auto& message : simulator.getMachine()->getMessages())
    {
        ui->logs->appendPlainText("[" + timestamp + "] -> " +
                                  convertType(message->getType()) + " | " +
                                  QString::fromStdString(message->getContent()) + '\n');
        if (message->getType() == simulator::ComponentMessageType::SEVERE)
        {
            createAlarmPopup(QString::fromStdString(message->getContent()), nullptr, nullptr);
        }
    }

    mappings->tab_input_registers[24] = 0;
    mappings->tab_input_registers[25] = 0;

    m_listener = std::make_shared<LogsMessageReceiver>(*this);
    simulator.getMachine()->getExternalMessageReceivers().push_back(m_listener);
}

void Logs::createAlarmPopup(QString message, QWidget *component, QWidget *parent)
{
    AlarmAlert *aa = new AlarmAlert(message, m_simulator, component, parent);
    aa->show();

    if (message == "The Emergency Button was triggered!")
    {
        m_toggle = new BitToggleThread(24, m_mappings);
        m_toggle->start();
    }
    else if (message == "A paper jammed the machine!")
    {
        m_toggle = new BitToggleThread(25, m_mappings);
        m_toggle->start();
    }
}

Logs::LogsMessageReceiver::LogsMessageReceiver(Logs& logs) : m_logs(logs) {}

void Logs::LogsMessageReceiver::ReceiveMessage(std::shared_ptr<simulator::ComponentMessage> message)
{
    auto timestamp = QTime::currentTime().toString("hh:mm:ss.zzz");
    m_logs.ui->logs->appendPlainText("[" + timestamp + "] -> " +
                                     m_logs.convertType(message->getType()) + " | " +
                                     QString::fromStdString(message->getContent()) + '\n');
    // Invoke pop-up for message
    QMetaObject::invokeMethod(&m_logs, "createAlarmPopup", Qt::QueuedConnection,
                              Q_ARG(QString, QString::fromStdString(message->getContent())),
                              Q_ARG(QWidget * , nullptr), Q_ARG(QWidget * , nullptr));
}

Logs::~Logs()
{
    delete ui;
}
