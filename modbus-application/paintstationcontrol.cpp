#include "countlistener.h"
#include "messagealert.h"
#include "paintstationcontrol.h"
#include "ui_paintstationcontrol.h"
#include "valueinput.h"

#include <QDesktopWidget>
#include <QFontDatabase>
#include <QInputDialog>
#include <QMessageBox>

PaintStationControl::PaintStationControl(PaintStation& paintStation, QWidget *parent) :
    QWidget(parent),
    paintStation(paintStation),
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

    countListener = std::make_shared<CountListener>(paintStation, ui->count, ui->percentage);
    paintStation.getCountMessageReceiver().push_back(countListener);
}

PaintStationControl::~PaintStationControl()
{
    delete ui;
}

void PaintStationControl::windowActivationChange(bool oldChange)
{
    if (oldChange) {
        hide();
    }
}

void PaintStationControl::on_ok_clicked()
{
    hide();
}

void PaintStationControl::on_edit_clicked()
{
    int maxNew = paintStation.getCapacity() - paintStation.getCount();
    maxNew = (maxNew / 100) * 100;
    if (maxNew < 1) {

        MessageAlert * ma = new MessageAlert("Paint Station", QString("There has to be atleast 100ml of paint missing!"), this);
        return;
    }

    auto callback = [=](std::string number) {
        try {
            int paper = atoi(number.c_str());
            if (paper < 0 || paper > maxNew) {
                MessageAlert * ma = new MessageAlert("Paint Station", QString("There has to be atleast 100 papers in delivery!"), this);
                return;
            }
            paintStation.modifyCount(paper);
        } catch (std::exception &e) {
            MessageAlert * ma = new MessageAlert("Paint Station", e.what(), this);
        }
    };

    ValueInput * input = new ValueInput("Paint Station",
                                        QString("Ammount of paint to add (0 - " + QString::number(maxNew) + ")."),
                                        this, callback);
}

void PaintStationControl::on_failure_clicked()
{
    hide();
    paintStation.Emit(Severe, paintStation.getName() + " has stopped working!");
}
