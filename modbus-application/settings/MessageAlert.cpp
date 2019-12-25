#include "MessageAlert.h"
#include "ui_MessageAlert.h"

#include <QDesktopWidget>
#include <QFontDatabase>

MessageAlert::MessageAlert(QString title, QString message, QWidget *parent) :
        QDialog(parent),
        ui(new Ui::MessageAlert)
{
    int width = 360;
    int height = 180;
    int x = (QApplication::desktop()->width() - width) / 2;
    int y = (QApplication::desktop()->height() - height) / 2;
    move(x, y);
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    ui->ok->setIcon(QIcon(":/Icons/ico_close_white.svg"));

    QFont robotoBold18(QFontDatabase::applicationFontFamilies(2).at(0), 14, QFont::DemiBold);
    ui->title->setFont(robotoBold18);
    QFont robotoMedium16(QFontDatabase::applicationFontFamilies(0).at(0), 12, QFont::DemiBold);
    ui->message->setFont(robotoMedium16);

    ui->title->setText(title);
    ui->message->setText(message);
}

void MessageAlert::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::ActivationChange && !this->isActiveWindow())
    {
        this->done(0);
    }
}

void MessageAlert::on_ok_clicked()
{
    this->done(0);
}

MessageAlert::~MessageAlert()
{
    qDebug("Destroyed MessageAlert!");
    delete ui;
}
