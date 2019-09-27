#include "countlistener.h"
#include "deliverycontrol.h"
#include "ui_deliverycontrol.h"

#include <math.h>
#include <QInputDialog>
#include <QMessageBox>


DeliveryControl::DeliveryControl(Delivery &delivery, QWidget *parent) :
    QWidget(parent),
    delivery(delivery),
    ui(new Ui::DeliveryControl)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    ui->name->setText("<h2> " + QString::fromStdString(delivery.getName()) + "</h2>");

    ui->count->setText("<h2>" + QString::number(delivery.getCount()) + "</h2>");
    ui->percentage->setText("<h2>" + QString::number(std::round(delivery.getPercentage() * 100)) + "% </h2>");

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
        QMessageBox * qb = new QMessageBox(this);
        qb->setText(QString("There has to be atleast 100 papers in delivery!"));
        qb->exec();
        return;
    }

    bool ok;
    QString number = QInputDialog::getText(0, "Delivery",
                                         QString("Ammount of paper to remove (0 - " + QString::number(maxNew) + ")."),
                                         QLineEdit::Normal, "", &ok);

    try {
        int paper = number.toInt();
        if (paper < 0 || paper > maxNew) {
            QMessageBox * qb = new QMessageBox(this);
            qb->setText(QString("The ammount you entered is not in range (0 - " + QString::number(maxNew) + ")."));
            qb->exec();
            return;
        }
        delivery.modifyCount(paper);
    } catch (std::exception &e) {
        QMessageBox * qb = new QMessageBox(this);
        qb->setText(e.what());
        qb->exec();
    }
}

void DeliveryControl::on_failure_clicked()
{
    hide();
    delivery.Emit(Severe, delivery.getName() + " has stopped working!");
}
