#ifndef SETTINGS_H
#define SETTINGS_H

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
    modbus_t * modbus;
    modbus_mapping_t * mapping;

public:
    Settings(Simulator& simulator, QWidget *parent = nullptr);
    ~Settings();

private:
    Ui::Settings *ui;
    void loop();
};

#endif // SETTINGS_H
