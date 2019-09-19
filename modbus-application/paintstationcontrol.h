#ifndef PAINTSTATIONCONTROL_H
#define PAINTSTATIONCONTROL_H

#include <QWidget>

#include <Components/PaintStation.h>

namespace Ui {
class PaintStationControl;
}

class PaintStationControl : public QWidget
{
    Q_OBJECT

public:
    explicit PaintStationControl(PaintStation& paintStation, QWidget *parent = nullptr);
    ~PaintStationControl();

private:
    Ui::PaintStationControl *ui;
    PaintStation& paintStation;
};

#endif // PAINTSTATIONCONTROL_H
