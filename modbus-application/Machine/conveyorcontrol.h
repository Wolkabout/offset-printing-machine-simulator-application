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
    void windowActivationChange(bool) override;

private slots:
    void on_decrease_clicked();

    void on_increase_clicked();

    void on_failure_clicked();

    void on_ok_clicked();

private:
    Ui::ConveyorControl *ui;
    Conveyor& m_conveyor;
    std::shared_ptr<ConveyorRateMessageReceiver> m_listener;
};

#endif // CONVEYORCONTROL_H
