#include "valueinput.h"
#include "ui_valueinput.h"

ValueInput::ValueInput(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ValueInput)
{
    ui->setupUi(this);
}

ValueInput::~ValueInput()
{
    delete ui;
}
