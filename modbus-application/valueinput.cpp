#include "valueinput.h"
#include "ui_valueinput.h"

#include <QFontDatabase>

ValueInput::ValueInput(QString title, QString message, QWidget *parent, std::function<void (std::string)> callback) :
    QWidget(parent),
    ui(new Ui::ValueInput),
    callback(callback)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    ui->ok->setIcon(QIcon(":/Icons/Resources/ico_close.svg"));

    QFont robotoBold18(QFontDatabase::applicationFontFamilies(2).at(0), 14, QFont::DemiBold);
    ui->name->setFont(robotoBold18);
    QFont robotoMedium16(QFontDatabase::applicationFontFamilies(0).at(0), 12, QFont::DemiBold);
    ui->desc->setFont(robotoMedium16);
    ui->input->setFont(robotoMedium16);
    ui->cancel->setFont(robotoMedium16);
    ui->apply->setFont(robotoMedium16);

    ui->name->setText(title);
    ui->desc->setText(message);

    show();
}

void ValueInput::on_ok_clicked()
{
    close();
}

ValueInput::~ValueInput()
{
    delete ui;
}

void ValueInput::on_apply_clicked()
{
    if (callback != nullptr) {
        callback(ui->input->text().toStdString());
    }
    close();
}

void ValueInput::on_cancel_clicked()
{
    close();
}
