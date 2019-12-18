#include "conveyorcontrol.h"
#include "ratelistener.h"
#include "ui_conveyorcontrol.h"

#include <QDesktopWidget>
#include <QFontDatabase>

ConveyorControl::ConveyorControl(Conveyor& conveyor, QWidget *parent) :
    QWidget(parent),
    m_conveyor(conveyor),
    ui(new Ui::ConveyorControl)
{
    int width = 400;
    int height = 440;
    int x = (QApplication::desktop()->width() - width) / 2;
    int y = (QApplication::desktop()->height() - height) / 2;
    move(x, y);
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    QFont robotoBold18(QFontDatabase::applicationFontFamilies(2).at(0), 14, QFont::DemiBold);
    ui->name->setFont(robotoBold18);
    QFont robotoMedium16(QFontDatabase::applicationFontFamilies(0).at(0), 12, QFont::DemiBold);
    ui->failure->setFont(robotoMedium16);
    ui->rate->setFont(robotoMedium16);
    QFont robotoMedium14(QFontDatabase::applicationFontFamilies(0).at(0), 10, QFont::DemiBold);
    ui->rateTitle->setFont(robotoMedium14);

    ui->ok->setIcon(QIcon(":/Icons/ico_close.svg"));
    ui->increase->setIcon(QIcon(":/Icons/ico_plus.svg"));
    ui->decrease->setIcon(QIcon(":/Icons/ico_minus.svg"));

    ui->rate->setText(QString::number(conveyor.getRatePerHour()));

    m_listener = std::make_shared<RateListener>(conveyor, ui->rate);
    conveyor.getRateMessageReceivers().push_back(m_listener);
}

ConveyorControl::~ConveyorControl()
{
    delete ui;
}

void ConveyorControl::windowActivationChange(bool oldChange)
{
    if (oldChange) {
        hide();
    }
}

void ConveyorControl::on_decrease_clicked()
{
    if (m_conveyor.getRatePerHour() > m_conveyor.getMinRatePerHour()) {
        m_conveyor.setRatePerHour(m_conveyor.getRatePerHour() - 100);
    }
}

void ConveyorControl::on_increase_clicked()
{
    if (m_conveyor.getRatePerHour() < m_conveyor.getMaxRatePerHour()) {
        m_conveyor.setRatePerHour(m_conveyor.getRatePerHour() + 100);
    }
}

void ConveyorControl::on_failure_clicked()
{
    hide();
    m_conveyor.Emit(Severe, m_conveyor.getName() + " has stopped working!");
}

void ConveyorControl::on_ok_clicked()
{
    hide();
}
