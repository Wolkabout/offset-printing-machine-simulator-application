#include "logs.h"
#include "ui_logs.h"

Logs::Logs(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Logs)
{
    ui->setupUi(this);
}

Logs::~Logs()
{
    delete ui;
}
