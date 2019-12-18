#ifndef DELIVERYCONTROL_H
#define DELIVERYCONTROL_H

#include <QLabel>
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
    void windowActivationChange(bool) override;

private slots:
    void on_edit_clicked();

    void on_failure_clicked();

    void on_ok_clicked();

private:
    Ui::DeliveryControl *ui;
    Delivery& m_delivery;
    std::shared_ptr<CountMessageReceiver> countListener;
};

#endif // DELIVERYCONTROL_H
