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
    void windowActivationChange(bool) override;

private slots:
    void on_edit_clicked();

    void on_failure_clicked();

    void on_ok_clicked();

private:
    Ui::PaintStationControl *ui;
    PaintStation& m_paintStation;
    std::shared_ptr<CountMessageReceiver> m_countListener;
};

#endif // PAINTSTATIONCONTROL_H
