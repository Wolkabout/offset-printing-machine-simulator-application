#include "deliverycontrol.h"
#include "ui_deliverycontrol.h"



DeliveryControl::DeliveryControl(Delivery &delivery, QWidget *parent) :
    QWidget(parent),
    delivery(delivery),
    ui(new Ui::DeliveryControl)
{
    ui->setupUi(this);
}

DeliveryControl::~DeliveryControl()
{
    delete ui;
}
