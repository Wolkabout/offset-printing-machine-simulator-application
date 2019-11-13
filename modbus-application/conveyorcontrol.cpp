#include "conveyorcontrol.h"
#include "ratelistener.h"
#include "ui_conveyorcontrol.h"

#include <QDesktopWidget>
#include <QFontDatabase>

ConveyorControl::ConveyorControl(Conveyor& conveyor, QWidget *parent) :
    QWidget(parent),
    conveyor(conveyor),
    ui(new Ui::ConveyorControl)
{
    setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            size(),
            qApp->desktop()->availableGeometry()
        )
    );
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

    ui->ok->setIcon(QIcon(":/Icons/Resources/ico_close.svg"));
    ui->increase->setIcon(QIcon(":/Icons/Resources/ico_plus.svg"));
    ui->decrease->setIcon(QIcon(":/Icons/Resources/ico_minus.svg"));

    ui->rate->setText(QString::number(conveyor.getRatePerHour()));

    listener = std::make_shared<RateListener>(conveyor, ui->rate);
    conveyor.getRateMessageReceivers().push_back(listener);
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
    if (conveyor.getRatePerHour() > conveyor.getMinRatePerHour()) {
        conveyor.setRatePerHour(conveyor.getRatePerHour() - 100);
    }
}

void ConveyorControl::on_increase_clicked()
{
    if (conveyor.getRatePerHour() < conveyor.getMaxRatePerHour()) {
        conveyor.setRatePerHour(conveyor.getRatePerHour() + 100);
    }
}

void ConveyorControl::on_failure_clicked()
{
    hide();
    conveyor.Emit(Severe, conveyor.getName() + " has stopped working!");
}

void ConveyorControl::on_ok_clicked()
{
    hide();
}
