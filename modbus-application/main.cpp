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

    QFrame * parent = w.frameHolder();
    int logIndex = windowManager.addFrame(std::make_shared<Logs>(simulator, parent)); // 0
    int settingsIndex = windowManager.addFrame(std::make_shared<Settings>(simulator, parent)); // 1
    int machineIndex = windowManager.addFrame(std::make_shared<MachineView>(simulator, parent)); // 2

    return a.exec();
}
