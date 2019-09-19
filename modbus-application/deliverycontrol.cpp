#include "deliverycontrol.h"
#include "ui_deliverycontrol.h"

#include <QInputDialog>
#include <QMessageBox>



DeliveryControl::DeliveryControl(Delivery &delivery, QWidget *parent) :
    QWidget(parent),
    delivery(delivery),
    ui(new Ui::DeliveryControl)
{
    ui->setupUi(this);
    ui->name->setText("<h2> " + QString::fromStdString(delivery.getName()) + "</h2>");

    countListener = std::make_shared<ComponentCountListener>(*this, delivery, ui->count, ui->percentage);
    delivery.getCountMessageReceiver().push_back(countListener);

    ui->count->setText("<h2>" + QString::number(delivery.getCount()) + "</h2>");
    ui->percentage->setText("<h2>" + QString::number(delivery.getPercentage() * 100) + "% </h2>");
}

DeliveryControl::ComponentCountListener::ComponentCountListener(DeliveryControl& dc, TempoComponent& tempoComponent, QLabel * countLabel, QLabel * percentageLabel)
    : dc(dc), tempoComponent(tempoComponent), countLabel(countLabel), percentageLabel(percentageLabel) { }

void DeliveryControl::ComponentCountListener::ReceiveMessage(std::shared_ptr<CountMessage> message) {
    QMetaObject::invokeMethod(countLabel, "setText", Qt::QueuedConnection, Q_ARG(QString, "<h2>" + QString::number(message->getCount()) + "</h2>"));
    QMetaObject::invokeMethod(percentageLabel, "setText", Qt::QueuedConnection, Q_ARG(QString, "<h2>" + QString::number(message->getPercentage() * 100) + "% </h2>"));
};

DeliveryControl::~DeliveryControl()
{
    delete ui;
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
