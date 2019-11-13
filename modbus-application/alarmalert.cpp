#include "alarmalert.h"
#include "ui_alarmalert.h"

#include <QFontDatabase>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QObject>

AlarmAlert::AlarmAlert(QString message, Simulator& simulator, QWidget* component, QWidget *parent) :
    QWidget(parent),
    message(message),
    component(component),
    simulator(simulator),
    ui(new Ui::AlarmAlert)
{
    int x = (QApplication::desktop()->width() - size().width()) / 2;
    int y = (QApplication::desktop()->height() - size().height()) / 2;
    move(x, y);
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    ui->ok->setIcon(QIcon(":/Icons/Resources/ico_close.svg"));

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
    if (message.contains("Feeder")) {
        simulator.getFeederWidget()->show();
    } else if (message.contains("Cyan")) {
        simulator.getCyanWidget()->show();
    } else if (message.contains("Magenta")) {
        simulator.getMagentaWidget()->show();
    } else if (message.contains("Yellow")) {
        simulator.getYellowWidget()->show();
    } else if (message.contains("Black")) {
        simulator.getBlackWidget()->show();
    } else if (message.contains("Delivery")) {
        simulator.getDeliveryWidget()->show();
    }
    hide();
}
