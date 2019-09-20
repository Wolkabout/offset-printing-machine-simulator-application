#ifndef PAINTSTATIONCONTROL_H
#define PAINTSTATIONCONTROL_H

#include <QLabel>
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

private slots:
    void on_edit_clicked();

    void on_failure_clicked();

    void on_ok_clicked();

private:
    Ui::PaintStationControl *ui;
    PaintStation& paintStation;
    std::shared_ptr<CountMessageReceiver> countListener;
};

#endif // PAINTSTATIONCONTROL_H
