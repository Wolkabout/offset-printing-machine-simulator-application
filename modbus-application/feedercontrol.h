#ifndef FEEDERCONTROL_H
#define FEEDERCONTROL_H

#include <QLabel>
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
    void windowActivationChange(bool) override;

private slots:
    void on_ok_clicked();

    void on_edit_clicked();

    void on_failure_clicked();

private:
    Ui::FeederControl *ui;
    Feeder &feeder;
    std::shared_ptr<CountMessageReceiver> countListener;
};

#endif // FEEDERCONTROL_H
