#ifndef CONVEYORCONTROL_H
#define CONVEYORCONTROL_H

#include "components/Conveyor.h"

#include <QWidget>

namespace Ui
{
    class ConveyorControl;
}

class ConveyorControl : public QWidget
{
    Q_OBJECT

public:
    ConveyorControl(simulator::Conveyor& conveyor, QWidget *parent = nullptr);

    ~ConveyorControl();

private slots:
    void on_decrease_clicked();

    void on_increase_clicked();

    void on_failure_clicked();

    void on_ok_clicked();

private:
    void changeEvent(QEvent *) override;

    simulator::Conveyor& m_conveyor;
    std::shared_ptr<simulator::ConveyorRateMessageReceiver> m_listener;
    Ui::ConveyorControl *ui;
};

#endif // CONVEYORCONTROL_H
