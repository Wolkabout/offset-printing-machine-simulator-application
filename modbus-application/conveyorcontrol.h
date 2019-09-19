#ifndef CONVEYORCONTROL_H
#define CONVEYORCONTROL_H

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

private:
    Ui::ConveyorControl *ui;
    Conveyor& conveyor;
};

#endif // CONVEYORCONTROL_H
