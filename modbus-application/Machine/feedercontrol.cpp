#include "countlistener.h"
#include "feedercontrol.h"
#include "Settings/messagealert.h"
#include "ui_feedercontrol.h"
#include "valueinput.h"

#include <QDesktopWidget>
#include <QFontDatabase>
#include <QInputDialog>
#include <QMessageBox>
#include <QMovie>
#include <QPicture>

FeederControl::FeederControl(Feeder &feeder, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FeederControl),
    m_feeder(feeder)
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

    countListener = std::make_shared<CountListener>(feeder, ui->count, ui->percentage);
    feeder.getCountMessageReceiver().push_back(countListener);
}

FeederControl::~FeederControl()
{
    delete ui;
}

void FeederControl::windowActivationChange(bool oldActive)
{
    if (oldActive) {
        hide();
    }
}

void FeederControl::on_ok_clicked()
{
    hide();
}

void FeederControl::on_edit_clicked()
{
    int maxNew = m_feeder.getCapacity() - m_feeder.getCount();
    maxNew = (maxNew / 100) * 100;
    if (maxNew < 1) {
        MessageAlert * ma = new MessageAlert("Feeder", "There has to be atleast 100 papers missing!", this);
        return;
    }

    auto callback = [=](std::string number) {
        try {
            int paper = atoi(number.c_str());
            if (paper < 0 || paper > maxNew) {
                MessageAlert * ma = new MessageAlert("Feeder", "The amount is not in range (0 - " + QString::number(maxNew) + ").", this);
                return;
            }
            m_feeder.modifyCount(paper);
        } catch (std::exception &e) {
            MessageAlert * ma = new MessageAlert("Feeder", e.what(), this);
        }
    };

    ValueInput * input = new ValueInput("Feeder",
                                        QString("Amount of paper to add (0 - " + QString::number(maxNew) + ")."),
                                        this, callback);
}

void FeederControl::on_failure_clicked()
{
    hide();
    m_feeder.Emit(Severe, m_feeder.getName() + " has stopped working!");
}
