#include "CountListener.h"
#include "DeliveryControl.h"
#include "settings/MessageAlert.h"
#include "ui_DeliveryControl.h"
#include "ValueInput.h"

#include <cmath>
#include <QDesktopWidget>
#include <QFontDatabase>

DeliveryControl::DeliveryControl(simulator::Delivery& delivery, QWidget *parent) :
        QWidget(parent),
        m_delivery(delivery),
        ui(new Ui::DeliveryControl)
{
    int width = 400;
    int height = 360;
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
    ui->edit->setFont(robotoMedium16);
    QFont robotoMedium14(QFontDatabase::applicationFontFamilies(0).at(0), 10, QFont::DemiBold);
    ui->countTitle->setFont(robotoMedium14);
    ui->percentageTitle->setFont(robotoMedium14);
    QFont robotoMedium18(QFontDatabase::applicationFontFamilies(0).at(0), 14, QFont::DemiBold);
    ui->count->setFont(robotoMedium18);
    ui->percentage->setFont(robotoMedium18);

    ui->ok->setIcon(QIcon(":/Icons/ico_close.svg"));

    ui->count->setText(QString::number(delivery.getCount()));
    ui->percentage->setText(QString::number(std::round(delivery.getPercentage() * 100)) + "%");

    m_countListener = std::make_shared<CountListener>(delivery, ui->count, ui->percentage);
    delivery.getCountMessageReceiver().push_back(m_countListener);
}

void DeliveryControl::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::ActivationChange && !this->isActiveWindow())
    {
        this->hide();
    }
}

void DeliveryControl::on_ok_clicked()
{
    this->hide();
}

void DeliveryControl::on_edit_clicked()
{
    int maxNew = m_delivery.getCount();
    maxNew = (maxNew / 100) * 100;
    if (maxNew < 1)
    {
        MessageAlert("Delivery",
                     QString("There has to be atleast 100 papers in delivery!"), this).exec();
        return;
    }

    auto callback = [=](std::string number) {
        try
        {
            int paper = atoi(number.c_str());
            if (paper < 0 || paper > maxNew)
            {
                MessageAlert("Delivery",
                             QString("The ammount you entered is not in range (0 - " +
                             QString::number(maxNew) + ")."), this).exec();
                return;
            }
            m_delivery.modifyCount(paper);
        }
        catch (std::exception& e)
        {
            MessageAlert("Delivery", e.what(), this).exec();
        }
    };

    ValueInput("Delivery",
               QString("Amount of paper to remove (0 - " +
               QString::number(maxNew) + ")."),
               this, callback).exec();
}

void DeliveryControl::on_failure_clicked()
{
    this->hide();
    m_delivery.Emit(simulator::ComponentMessageType::SEVERE, m_delivery.getName() + " has stopped working!");
}

DeliveryControl::~DeliveryControl()
{
    delete ui;
}
