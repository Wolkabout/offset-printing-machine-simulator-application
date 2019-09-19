#ifndef CONVEYORCONTROL_H
#define CONVEYORCONTROL_H

#include <QLabel>
#include <QWidget>

#include <Components/Conveyor.h>

namespace Ui {
class ConveyorControl;
}

class ConveyorControl : public QWidget
{
    Q_OBJECT

public:
    ConveyorControl(Conveyor& conveyor, QWidget *parent = nullptr);
    ~ConveyorControl();

private slots:
    void on_decrease_clicked();

    void on_increase_clicked();

    void on_failure_clicked();

    void on_ok_clicked();

private:
    Ui::ConveyorControl *ui;
    Conveyor& conveyor;
    std::shared_ptr<ConveyorRateMessageReceiver> listener;

    class RateListener : public ConveyorRateMessageReceiver {
    private:
        ConveyorControl& cc;
        Conveyor& conveyor;
        QLabel * rateLabel;
    public:
        RateListener(ConveyorControl&, Conveyor&, QLabel *);
        void ReceiveMessage(std::shared_ptr<ConveyorRateMessage>) override;
    };
};

#endif // CONVEYORCONTROL_H
