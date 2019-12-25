#ifndef FEEDERCONTROL_H
#define FEEDERCONTROL_H

#include "components/Feeder.h"

#include <QLabel>
#include <QWidget>

namespace Ui
{
    class FeederControl;
}

class FeederControl : public QWidget
{
    Q_OBJECT

public:
    FeederControl(simulator::Feeder& feeder, QWidget *parent = nullptr);

    ~FeederControl();

private slots:
    void on_ok_clicked();

    void on_edit_clicked();

    void on_failure_clicked();

private:
    void changeEvent(QEvent *) override;

    simulator::Feeder& m_feeder;
    std::shared_ptr<simulator::CountMessageReceiver> m_countListener;
    Ui::FeederControl *ui;
};

#endif // FEEDERCONTROL_H
