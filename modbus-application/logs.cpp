#include "logs.h"
#include "ui_logs.h"

Logs::Logs(Simulator& simulator, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Logs),
    simulator(simulator)
{
    ui->setupUi(this);
}

Logs::~Logs()
{
    delete ui;
}
