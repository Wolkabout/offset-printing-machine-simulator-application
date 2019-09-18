#ifndef FEEDERCONTROL_H
#define FEEDERCONTROL_H

#include <QWidget>

namespace Ui {
class FeederControl;
}

class FeederControl : public QWidget
{
    Q_OBJECT

public:
    explicit FeederControl(QWidget *parent = nullptr);
    ~FeederControl();

private:
    Ui::FeederControl *ui;
};

#endif // FEEDERCONTROL_H
