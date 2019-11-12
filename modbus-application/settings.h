#ifndef SETTINGS_H
#define SETTINGS_H

#include "modbusthread.h"
#include "simulator.h"
#include <modbus/modbus-tcp.h>
#include <QFrame>

namespace Ui {
class Settings;
}

class Settings : public QFrame
{
    Q_OBJECT
    Simulator& simulator;
    QString addressString;
    ModbusThread &thread;

public:
    Settings(Simulator& simulator, ModbusThread &thread, QWidget *parent = nullptr);
    ~Settings();

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
