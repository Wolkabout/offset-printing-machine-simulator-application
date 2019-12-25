#ifndef PAINTSTATIONCONTROL_H
#define PAINTSTATIONCONTROL_H

#include "components/PaintStation.h"

#include <QLabel>
#include <QWidget>

namespace Ui
{
    class PaintStationControl;
}

class PaintStationControl : public QWidget
{
    Q_OBJECT

public:
    PaintStationControl(simulator::PaintStation& paintStation, QWidget *parent = nullptr);

    ~PaintStationControl();

private slots:
    void on_edit_clicked();

    void on_failure_clicked();

    void on_ok_clicked();

private:
    void changeEvent(QEvent *) override;

    simulator::PaintStation& m_paintStation;
    std::shared_ptr<simulator::CountMessageReceiver> m_countListener;
    Ui::PaintStationControl *ui;
};

#endif // PAINTSTATIONCONTROL_H
