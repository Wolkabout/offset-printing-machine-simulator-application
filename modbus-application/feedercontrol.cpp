#include "feedercontrol.h"
#include "ui_feedercontrol.h"

#include <QInputDialog>
#include <QMessageBox>
#include <QMovie>

FeederControl::FeederControl(Feeder &feeder, QWidget *parent) :
    QWidget(parent),
    feeder(feeder),
    ui(new Ui::FeederControl)
{
    ui->setupUi(this);
    ui->name->setText("<h2>" + QString::fromStdString(feeder.getName()) + "</h2>");

    countListener = std::make_shared<ComponentCountListener>(*this, feeder, ui->count, ui->percentage);
    feeder.getCountMessageReceiver().push_back(countListener);

    ui->count->setText("<h2>" + QString::number(feeder.getCount()) + "</h2>");
    ui->percentage->setText("<h2>" + QString::number(feeder.getPercentage() * 100) + "% </h2>");
}

FeederControl::ComponentCountListener::ComponentCountListener(FeederControl& fc, TempoComponent& tempoComponent, QLabel * countLabel, QLabel * percentageLabel)
    : fc(fc), tempoComponent(tempoComponent), countLabel(countLabel), percentageLabel(percentageLabel) { }

void FeederControl::ComponentCountListener::ReceiveMessage(std::shared_ptr<CountMessage> message) {
    QMetaObject::invokeMethod(countLabel, "setText", Qt::QueuedConnection, Q_ARG(QString, "<h2>" + QString::number(message->getCount()) + "</h2>"));
    QMetaObject::invokeMethod(percentageLabel, "setText", Qt::QueuedConnection, Q_ARG(QString, "<h2>" + QString::number(message->getPercentage() * 100) + "% </h2>"));
};

FeederControl::~FeederControl()
{
    delete ui;
}

void FeederControl::on_ok_clicked()
{
    hide();
}

void FeederControl::on_edit_clicked()
{
    int maxNew = feeder.getCapacity() - feeder.getCount();
    maxNew = (maxNew / 100) * 100;
    if (maxNew < 1) {
        QMessageBox * qb = new QMessageBox(this);
        qb->setText(QString("There has to be atleast 100 papers missing!"));
        qb->exec();
        return;
    }

    bool ok;
    QString number = QInputDialog::getText(0, "Feeder",
                                         QString("Ammount of paper to add (0 - " + QString::number(maxNew) + ")."),
                                         QLineEdit::Normal, "", &ok);

    try {
        int paper = number.toInt();
        if (paper < 0 || paper > maxNew) {
            QMessageBox * qb = new QMessageBox(this);
            qb->setText(QString("The ammount you entered is not in range (0 - " + QString::number(maxNew) + ")."));
            qb->exec();
        }
        feeder.modifyCount(paper);
    } catch (std::exception &e) {
        QMessageBox * qb = new QMessageBox(this);
        qb->setText(e.what());
        qb->exec();
    }
}

void FeederControl::on_failure_clicked()
{
    hide();
    feeder.Emit(Severe, feeder.getName() + " has stopped working!");
}
