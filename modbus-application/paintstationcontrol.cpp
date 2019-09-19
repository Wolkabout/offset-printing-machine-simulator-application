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
    ui->name->setText("<h2>" + QString::fromStdString(paintStation.getName()) + "</h2>");

    countListener = std::make_shared<ComponentCountListener>(*this, paintStation, ui->count, ui->percentage);
    paintStation.getCountMessageReceiver().push_back(countListener);

    ui->count->setText("<h2>" + QString::number(paintStation.getCount()) + "</h2>");
    ui->percentage->setText("<h2>" + QString::number(paintStation.getPercentage() * 100) + "% </h2>");
    char paint = paintStation.getName()[0];
    if (paint == 'B') {
        paint = 'K';
    }
    std::string animationPath = ":/Animations/Resources/PaintStationAnimation" + std::string(1, paint) + "1.gif";
    ui->image->setPixmap(QPixmap(QString::fromStdString(animationPath)));
}

PaintStationControl::ComponentCountListener::ComponentCountListener(PaintStationControl& psc, TempoComponent& tempoComponent, QLabel * countLabel, QLabel * percentageLabel)
    : psc(psc), tempoComponent(tempoComponent), countLabel(countLabel), percentageLabel(percentageLabel) { }

void PaintStationControl::ComponentCountListener::ReceiveMessage(std::shared_ptr<CountMessage> message) {
    QMetaObject::invokeMethod(countLabel, "setText", Qt::QueuedConnection, Q_ARG(QString, "<h2>" + QString::number(message->getCount()) + "</h2>"));
    QMetaObject::invokeMethod(percentageLabel, "setText", Qt::QueuedConnection, Q_ARG(QString, "<h2>" + QString::number(message->getPercentage() * 100) + "% </h2>"));
};

PaintStationControl::~PaintStationControl()
{
    delete ui;
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
