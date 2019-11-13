#include "countlistener.h"
#include "deliverycontrol.h"
#include "messagealert.h"
#include "ui_deliverycontrol.h"
#include "valueinput.h"

#include <math.h>
#include <QDesktopWidget>
#include <QInputDialog>
#include <QMessageBox>
#include <QFontDatabase>


DeliveryControl::DeliveryControl(Delivery &delivery, QWidget *parent) :
    QWidget(parent),
    delivery(delivery),
    ui(new Ui::DeliveryControl)
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
    ui->edit->setFont(robotoMedium16);
    QFont robotoMedium14(QFontDatabase::applicationFontFamilies(0).at(0), 10, QFont::DemiBold);
    ui->countTitle->setFont(robotoMedium14);
    ui->percentageTitle->setFont(robotoMedium14);
    QFont robotoMedium18(QFontDatabase::applicationFontFamilies(0).at(0), 14, QFont::DemiBold);
    ui->count->setFont(robotoMedium18);
    ui->percentage->setFont(robotoMedium18);

    ui->ok->setIcon(QIcon(":/Icons/Resources/ico_close.svg"));

    ui->count->setText(QString::number(delivery.getCount()));
    ui->percentage->setText(QString::number(std::round(delivery.getPercentage() * 100)) + "%");

    countListener = std::make_shared<CountListener>(delivery, ui->count, ui->percentage);
    delivery.getCountMessageReceiver().push_back(countListener);
}

DeliveryControl::~DeliveryControl()
{
    delete ui;
}

void DeliveryControl::windowActivationChange(bool oldChange)
{
    if (oldChange) {
        hide();
    }
}

void DeliveryControl::on_ok_clicked()
{
    hide();
}

void DeliveryControl::on_edit_clicked()
{
    int maxNew = delivery.getCount();
    maxNew = (maxNew / 100) * 100;
    if (maxNew < 1) {
        MessageAlert * ma = new MessageAlert("Delivery", QString("There has to be atleast 100 papers in delivery!"), this);
        return;
    }

    auto callback = [=](std::string number) {
        try {
            int paper = atoi(number.c_str());
            if (paper < 0 || paper > maxNew) {
                MessageAlert * ma = new MessageAlert("Delivery", QString("The ammount you entered is not in range (0 - " + QString::number(maxNew) + ")."), this);
                return;
            }
            delivery.modifyCount(paper);
        } catch (std::exception &e) {
            MessageAlert * ma = new MessageAlert("Delivery", e.what(),this);
        }
    };

    ValueInput * input = new ValueInput("Delivery",
                                        QString("Amount of paper to remove (0 - " + QString::number(maxNew) + ")."),
                                        this, callback);
}

void DeliveryControl::on_failure_clicked()
{
    hide();
    delivery.Emit(Severe, delivery.getName() + " has stopped working!");
}
