#ifndef SETTINGS_H
#define SETTINGS_H

#include "simulator.h"

#include <QFrame>

namespace Ui {
class Settings;
}

class Settings : public QFrame
{
    Q_OBJECT
    Simulator& simulator;

public:
    Settings(Simulator& simulator, QWidget *parent = nullptr);
    ~Settings();

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
