#ifndef SETTINGS_H
#define SETTINGS_H

#include "Configurations.h"
#include "external/ModbusThread.h"
#include "modbus/modbus-tcp.h"
#include "Simulator.h"

#include <QFrame>
#include <QLineEdit>

#define DEFAULT_FEEDER 17000
#define DEFAULT_CYAN 10000
#define DEFAULT_MAGENTA 10000
#define DEFAULT_YELLOW 10000
#define DEFAULT_BLACK 10000
#define DEFAULT_DELIVERY 0
#define DEFAULT_CONVEYOR 14400

namespace Ui
{
    class Settings;
}

class Settings : public QFrame
{
    Q_OBJECT
public:
    Settings(const Simulator& simulator, ModbusThread& thread, QWidget *parent = nullptr);

    ~Settings();

    std::vector<int> load();

    void place(std::vector<int>);

private slots:
    void on_toggle_clicked();

    void on_cancel_clicked();

    void on_apply_clicked();

    void on_reset_clicked();

private:
    const Simulator& m_simulator;
    ModbusThread& m_thread;
    QString m_addressString;
    bool m_toggled;
    std::vector<int> m_currentConfig;
    std::vector<QLineEdit *> m_forms;
    Ui::Settings *ui;
};

#endif // SETTINGS_H
