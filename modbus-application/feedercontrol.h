#ifndef FEEDERCONTROL_H
#define FEEDERCONTROL_H

#include <QWidget>

#include <Components/Feeder.h>

namespace Ui {
class FeederControl;
}

class FeederControl : public QWidget
{
    Q_OBJECT

public:
    FeederControl(Feeder &feeder, QWidget *parent = nullptr);
    ~FeederControl();

private:
    Ui::FeederControl *ui;
    Feeder &feeder;
};

#endif // FEEDERCONTROL_H
