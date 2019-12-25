#include "CountListener.h"
#include "FeederControl.h"
#include "settings/MessageAlert.h"
#include "ui_FeederControl.h"
#include "ValueInput.h"

#include <QDesktopWidget>
#include <QFontDatabase>
#include <QMovie>
#include <QPicture>

FeederControl::FeederControl(simulator::Feeder& feeder, QWidget *parent) :
        QWidget(parent),
        m_feeder(feeder),
        ui(new Ui::FeederControl)
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

    ui->count->setText(QString::number(feeder.getCount()));
    ui->percentage->setText(QString::number(feeder.getPercentage() * 100) + "%");

    m_countListener = std::make_shared<CountListener>(feeder, ui->count, ui->percentage);
    feeder.getCountMessageReceiver().push_back(m_countListener);
}

void FeederControl::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::ActivationChange && !this->isActiveWindow())
    {
        this->hide();
    }
}

void FeederControl::on_ok_clicked()
{
    this->hide();
}

void FeederControl::on_edit_clicked()
{
    int maxNew = m_feeder.getCapacity() - m_feeder.getCount();
    maxNew = (maxNew / 100) * 100;
    if (maxNew < 1)
    {
        MessageAlert("Feeder", "There has to be atleast 100 papers missing!", this).exec();
        return;
    }

    auto callback = [=](std::string number) {
        try
        {
            int paper = atoi(number.c_str());
            if (paper < 0 || paper > maxNew)
            {
                MessageAlert("Feeder", "The amount is not in range (0 - " +
                             QString::number(maxNew) + ").", this).exec();
                return;
            }
            m_feeder.modifyCount(paper);
        }
        catch (std::exception& e)
        {
            MessageAlert("Feeder", e.what(), this).exec();
        }
    };

    ValueInput("Feeder", QString("Amount of paper to add (0 - " +
               QString::number(maxNew) + ")."), this, callback).exec();
}

void FeederControl::on_failure_clicked()
{
    this->hide();
    m_feeder.Emit(simulator::ComponentMessageType::SEVERE, m_feeder.getName() + " has stopped working!");
}

FeederControl::~FeederControl()
{
    delete ui;
}
