#include "CountListener.h"
#include "settings/MessageAlert.h"
#include "PaintStationControl.h"
#include "ui_PaintStationControl.h"
#include "ValueInput.h"

#include <QDesktopWidget>
#include <QFontDatabase>

PaintStationControl::PaintStationControl(simulator::PaintStation& paintStation, QWidget *parent) :
        QWidget(parent),
        m_paintStation(paintStation),
        ui(new Ui::PaintStationControl)
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

    ui->name->setText(QString::fromStdString(paintStation.getName()));
    ui->count->setText(QString::number(paintStation.getCount()));
    ui->percentage->setText(QString::number(paintStation.getPercentage() * 100) + "%");
    std::string paint = paintStation.getName().substr(0, paintStation.getName().find(' '));
    std::string animationPath = ":/Images/" + paint + ".svg";
    ui->image->setPixmap(QPixmap(QString::fromStdString(animationPath)));

    m_countListener = std::make_shared<CountListener>(paintStation, ui->count, ui->percentage);
    paintStation.getCountMessageReceiver().push_back(m_countListener);
}

void PaintStationControl::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::ActivationChange && !this->isActiveWindow())
    {
        this->hide();
    }
}

void PaintStationControl::on_ok_clicked()
{
    this->hide();
}

void PaintStationControl::on_edit_clicked()
{
    int maxNew = m_paintStation.getCapacity() - m_paintStation.getCount();
    maxNew = (maxNew / 100) * 100;
    if (maxNew < 1)
    {

        MessageAlert("Paint Station",
                     QString("There has to be atleast 100ml of paint missing!"), this).exec();
        return;
    }

    auto callback = [=](std::string number) {
        try
        {
            int paper = atoi(number.c_str());
            if (paper < 0 || paper > maxNew)
            {
                MessageAlert("Paint Station",
                             QString("There has to be atleast 100 papers in delivery!"), this).exec();
                return;
            }
            m_paintStation.modifyCount(paper);
        }
        catch (std::exception& e)
        {
            MessageAlert("Paint Station", e.what(), this).exec();
        }
    };

    ValueInput("Paint Station",
               QString("Ammount of paint to add (0 - " + QString::number(maxNew) + ")."),
               this, callback).exec();
}

void PaintStationControl::on_failure_clicked()
{
    this->hide();
    m_paintStation.Emit(simulator::ComponentMessageType::SEVERE,
                        m_paintStation.getName() + " has stopped working!");
}

PaintStationControl::~PaintStationControl()
{
    delete ui;
}
