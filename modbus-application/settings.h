#ifndef SETTINGS_H
#define SETTINGS_H

#include "configurations.h"
#include "modbusthread.h"
#include "simulator.h"
#include <modbus/modbus-tcp.h>
#include <QFrame>
#include <QLineEdit>

namespace Ui {
class Settings;
}

class Settings : public QFrame
{
    Q_OBJECT
    Simulator& simulator;
    QString addressString;
    ModbusThread &thread;
    bool toggled;
    std::vector<int> currentConfig;
    std::vector<QLineEdit*> forms;
    Ui::Settings *ui;
public:
    Settings(Simulator& simulator, ModbusThread &thread, QWidget *parent = nullptr);
    ~Settings();
    std::vector<int> load();
    void place(std::vector<int>);

private slots:
    void on_toggle_clicked();

    void on_cancel_clicked();

    void on_apply_clicked();

    void on_reset_clicked();
};

#endif // SETTINGS_H
