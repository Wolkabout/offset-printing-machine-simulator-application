#include "ValueInput.h"
#include "ui_ValueInput.h"

#include <QFontDatabase>

ValueInput::ValueInput(QString title, QString message,
                       QWidget *parent, std::function<void(std::string)> callback) :
        QDialog(parent),
        m_callback(callback),
        ui(new Ui::ValueInput)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    ui->ok->setIcon(QIcon(":/Icons/ico_close.svg"));

    QFont robotoBold18(QFontDatabase::applicationFontFamilies(2).at(0), 14, QFont::DemiBold);
    ui->name->setFont(robotoBold18);
    QFont robotoMedium16(QFontDatabase::applicationFontFamilies(0).at(0), 12, QFont::DemiBold);
    ui->desc->setFont(robotoMedium16);
    ui->input->setFont(robotoMedium16);
    ui->cancel->setFont(robotoMedium16);
    ui->apply->setFont(robotoMedium16);

    ui->name->setText(title);
    ui->desc->setText(message);
}

void ValueInput::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::ActivationChange && !this->isActiveWindow())
    {
        this->done(0);
    }
}

void ValueInput::on_ok_clicked()
{
    this->done(0);
}

void ValueInput::on_apply_clicked()
{
    if (m_callback != nullptr)
    {
        m_callback(ui->input->text().toStdString());
    }
    this->done(0);
}

void ValueInput::on_cancel_clicked()
{
    this->done(0);
}

ValueInput::~ValueInput()
{
    qDebug("Destroyed ValueInput!");
    delete ui;
}
