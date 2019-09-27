#include "countlistener.h"
#include "paintstationcontrol.h"
#include "ui_paintstationcontrol.h"

#include <QInputDialog>
#include <QMessageBox>

PaintStationControl::PaintStationControl(PaintStation& paintStation, QWidget *parent) :
    QWidget(parent),
    paintStation(paintStation),
    ui(new Ui::PaintStationControl)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);

    ui->name->setText("<h2>" + QString::fromStdString(paintStation.getName()) + "</h2>");
    ui->count->setText("<h2>" + QString::number(paintStation.getCount()) + "</h2>");
    ui->percentage->setText("<h2>" + QString::number(paintStation.getPercentage() * 100) + "% </h2>");
    char paint = paintStation.getName()[0];
    if (paint == 'B') {
        paint = 'K';
    }
    std::string animationPath = ":/Animations/Resources/PaintStationAnimation" + std::string(1, paint) + "1.gif";
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
        QMessageBox * qb = new QMessageBox(this);
        qb->setText(QString("There has to be atleast 100ml of paint missing!"));
        qb->exec();
        return;
    }

    bool ok;
    QString number = QInputDialog::getText(0, "Paint Station",
                                         QString("Ammount of paint to add (0 - " + QString::number(maxNew) + ")."),
                                         QLineEdit::Normal, "", &ok);

    try {
        int paper = number.toInt();
        if (paper < 0 || paper > maxNew) {
            QMessageBox * qb = new QMessageBox(this);
            qb->setText(QString("The ammount you entered is not in range (0 - " + QString::number(maxNew) + ")."));
            qb->exec();
            return;
        }
        paintStation.modifyCount(paper);
    } catch (std::exception &e) {
        QMessageBox * qb = new QMessageBox(this);
        qb->setText(e.what());
        qb->exec();
    }
}

void PaintStationControl::on_failure_clicked()
{
    hide();
    paintStation.Emit(Severe, paintStation.getName() + " has stopped working!");
}
