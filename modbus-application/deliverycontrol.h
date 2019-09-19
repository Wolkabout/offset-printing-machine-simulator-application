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

private slots:
    void on_edit_clicked();

    void on_failure_clicked();

    void on_ok_clicked();

private:
    Ui::DeliveryControl *ui;
    Delivery& delivery;
    std::shared_ptr<CountMessageReceiver> countListener;

    class ComponentCountListener : public CountMessageReceiver {
    private:
        DeliveryControl& dc;
        TempoComponent& tempoComponent;
        QLabel * countLabel;
        QLabel * percentageLabel;
    public:
        ComponentCountListener(DeliveryControl&, TempoComponent&, QLabel *, QLabel *);
        void ReceiveMessage(std::shared_ptr<CountMessage>) override;
    };
};

#endif // DELIVERYCONTROL_H
