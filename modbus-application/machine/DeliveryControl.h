#ifndef DELIVERYCONTROL_H
#define DELIVERYCONTROL_H

#include "components/Delivery.h"

#include <QLabel>
#include <QWidget>

namespace Ui
{
    class DeliveryControl;
}

class DeliveryControl : public QWidget
{
    Q_OBJECT

public:
    DeliveryControl(simulator::Delivery& delivery, QWidget *parent = nullptr);

    ~DeliveryControl();

private slots:
    void on_edit_clicked();

    void on_failure_clicked();

    void on_ok_clicked();

private:
    void changeEvent(QEvent *) override;

    simulator::Delivery& m_delivery;
    std::shared_ptr<simulator::CountMessageReceiver> m_countListener;
    Ui::DeliveryControl *ui;
};

#endif // DELIVERYCONTROL_H
