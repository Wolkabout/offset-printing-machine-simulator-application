#include "paintstationcontrol.h"
#include "ui_paintstationcontrol.h"

PaintStationControl::PaintStationControl(PaintStation& paintStation, QWidget *parent) :
    QWidget(parent),
    paintStation(paintStation),
    ui(new Ui::PaintStationControl)
{
    ui->setupUi(this);
}

PaintStationControl::~PaintStationControl()
{
    delete ui;
}
