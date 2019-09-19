#ifndef DELIVERYCONTROL_H
#define DELIVERYCONTROL_H

#include <QWidget>

#include <Components/Delivery.h>

namespace Ui {
class DeliveryControl;
}

class DeliveryControl : public QWidget
{
    Q_OBJECT

public:
    DeliveryControl(Delivery& delivery, QWidget *parent = nullptr);
    ~DeliveryControl();

private:
    Ui::DeliveryControl *ui;
    Delivery& delivery;
};

#endif // DELIVERYCONTROL_H
