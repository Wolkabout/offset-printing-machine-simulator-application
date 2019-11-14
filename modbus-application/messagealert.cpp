#include "messagealert.h"
#include "ui_messagealert.h"

#include <QDesktopWidget>
#include <QFontDatabase>

MessageAlert::MessageAlert(QString title, QString message, QWidget *parent) :
    QWidget(parent),
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

    ui->ok->setIcon(QIcon(":/Icons/Resources/ico_close_white.svg"));

    QFont robotoBold18(QFontDatabase::applicationFontFamilies(2).at(0), 14, QFont::DemiBold);
    ui->title->setFont(robotoBold18);
    QFont robotoMedium16(QFontDatabase::applicationFontFamilies(0).at(0), 12, QFont::DemiBold);
    ui->message->setFont(robotoMedium16);

    ui->title->setText(title);
    ui->message->setText(message);
    show();
}

void MessageAlert::on_ok_clicked()
{
    close();
}

MessageAlert::~MessageAlert()
{
    delete ui;
}
