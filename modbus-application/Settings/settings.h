#ifndef SETTINGS_H
#define SETTINGS_H

#include "configurations.h"
#include "Modbus/modbusthread.h"
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
    Simulator& m_simulator;
    QString m_addressString;
    ModbusThread &m_thread;
    bool m_toggled;
    std::vector<int> m_currentConfig;
    std::vector<QLineEdit*> m_forms;
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
