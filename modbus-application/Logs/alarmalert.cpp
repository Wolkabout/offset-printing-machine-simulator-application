#include "alarmalert.h"
#include "ui_alarmalert.h"

#include <QFontDatabase>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QObject>

AlarmAlert::AlarmAlert(QString message, Simulator& simulator, QWidget* component, QWidget *parent) :
    QWidget(parent),
    m_message(message),
    m_component(component),
    ui(new Ui::AlarmAlert),
    m_simulator(simulator)
{
    int width = 360;
    int height = 216;
    int x = (QApplication::desktop()->width() - width) / 2;
    int y = (QApplication::desktop()->height() - height) / 2;
    move(x, y);
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    ui->ok->setIcon(QIcon(":/Icons/ico_close_white.svg"));

    QFont robotoBold18(QFontDatabase::applicationFontFamilies(2).at(0), 14, QFont::DemiBold);
    ui->title->setFont(robotoBold18);
    QFont robotoMedium16(QFontDatabase::applicationFontFamilies(0).at(0), 12, QFont::DemiBold);
    ui->goto_2->setFont(robotoMedium16);
    ui->message->setFont(robotoMedium16);

    if (!(message.contains("Feeder") || message.contains("Cyan") || message.contains("Magenta")
            || message.contains("Yellow") || message.contains("Black") || message.contains("Delivery"))) {
        ui->goto_2->setEnabled(false);
    }

    ui->message->setText(message);
    //    QMetaObject::invokeMethod(ui->message, "setText", Qt::QueuedConnection, Q_ARG(QString, message));
}

AlarmAlert::~AlarmAlert()
{
    delete ui;
}

void AlarmAlert::windowActivationChange(bool oldChange)
{
    if (oldChange) {
        hide();
    }
}

void AlarmAlert::on_ok_clicked()
{
    this->hide();
}

void AlarmAlert::on_goto_2_clicked()
{
    if (m_message.contains("Feeder")) {
        m_simulator.getFeederWidget()->show();
    } else if (m_message.contains("Cyan")) {
        m_simulator.getCyanWidget()->show();
    } else if (m_message.contains("Magenta")) {
        m_simulator.getMagentaWidget()->show();
    } else if (m_message.contains("Yellow")) {
        m_simulator.getYellowWidget()->show();
    } else if (m_message.contains("Black")) {
        m_simulator.getBlackWidget()->show();
    } else if (m_message.contains("Delivery")) {
        m_simulator.getDeliveryWidget()->show();
    }
    hide();
}
