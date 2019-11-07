#include "countlistener.h"
#include "feedercontrol.h"
#include "ui_feedercontrol.h"

#include <QFontDatabase>
#include <QInputDialog>
#include <QMessageBox>
#include <QMovie>

FeederControl::FeederControl(Feeder &feeder, QWidget *parent) :
    QWidget(parent),
    feeder(feeder),
    ui(new Ui::FeederControl)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

//    QFont robotoBold18(QFontDatabase::applicationFontFamilies(2).at(0), 14, QFont::DemiBold);
//    ui->name->setFont(robotoBold18);
//    QFont robotoMedium16(QFontDatabase::applicationFontFamilies(0).at(0), 12, QFont::DemiBold);
//    ui->failure->setFont(robotoMedium16);
//    ui->edit->setFont(robotoMedium16);

    ui->ok->setIcon(QIcon(":/Icons/Resources/ico_close.svg"));

    ui->count->setText("<h2>" + QString::number(feeder.getCount()) + "</h2>");
    ui->percentage->setText("<h2>" + QString::number(feeder.getPercentage() * 100) + "% </h2>");

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
            return;
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
