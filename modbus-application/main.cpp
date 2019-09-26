#include "logs.h"
#include "machineview.h"
#include "mainwindow.h"
#include "settings.h"
#include "simulator.h"
#include "windowmanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Simulator simulator;

    WindowManager windowManager;

    MainWindow w(simulator, windowManager);
    w.show();

    ModbusThread modbusThread(simulator);

    QFrame * parent = w.frameHolder();
    int logIndex = windowManager.addFrame(std::make_shared<Logs>(simulator, modbusThread.getMapping(), parent)); // 0
    int settingsIndex = windowManager.addFrame(std::make_shared<Settings>(simulator, modbusThread, parent)); // 1
    int machineIndex = windowManager.addFrame(std::make_shared<MachineView>(simulator, parent)); // 2

    modbusThread.start();

    return a.exec();
}
