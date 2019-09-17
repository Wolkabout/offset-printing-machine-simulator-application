#ifndef LOGS_H
#define LOGS_H

#include "simulator.h"

#include <QFrame>

namespace Ui {
class Logs;
}

class Logs : public QFrame
{
    Q_OBJECT
    Simulator& simulator;
public:
    Logs(Simulator& simulator, QWidget *parent = nullptr);
    ~Logs();

private:
    Ui::Logs *ui;
};

#endif // LOGS_H
