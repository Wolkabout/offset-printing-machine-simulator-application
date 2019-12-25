#include "logs/Logs.h"
#include "machine/MachineView.h"
#include "MainWindow.h"
#include "settings/Settings.h"
#include "Simulator.h"
#include "WindowManager.h"

#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    try
    {
        QApplication a(argc, argv);

#ifdef QT_DEBUG
        qDebug("Application is running in DEBUG mode!");
#endif

        Simulator simulator;

        QFontDatabase::addApplicationFont(":/Fonts/Roboto-Medium.ttf"); // id 0
        QFontDatabase::addApplicationFont(":/Fonts/Roboto-Regular.ttf"); // id 1
        QFontDatabase::addApplicationFont(":/Fonts/Roboto-Bold.ttf"); // id 2

        MainWindow w(simulator);
        w.show();

        ModbusThread modbusThread(simulator);
        WindowManager& windowManager = w.getWindowManager();

        QFrame *parent = w.frameHolder();
        windowManager.addFrame(std::make_shared<Logs>(simulator, modbusThread.getMapping(), parent)); // 0
        std::shared_ptr<Settings> settingsView = std::make_shared<Settings>(simulator, modbusThread, parent);
        windowManager.addFrame(settingsView); // 1
        std::shared_ptr<MachineView> machineView = std::make_shared<MachineView>(simulator, parent);
        windowManager.addFrame(machineView); // 2

        simulator.setFeederWidget(machineView->getFeederWidget());
        simulator.setCyanWidget(machineView->getCyanWidget());
        simulator.setMagentaWidget(machineView->getMagentaWidget());
        simulator.setYellowWidget(machineView->getYellowWidget());
        simulator.setBlackWidget(machineView->getBlackWidget());
        simulator.setDeliveryWidget(machineView->getDeliveyWidget());
        simulator.setConveyorWidget(machineView->getConveyorWidget());
        modbusThread.start();

        int res = a.exec();
        modbusThread.terminate();
        modbusThread.wait(5);
        return res;
    }
    catch (std::exception& e)
    {
        qErrnoWarning("%s", e.what());
        return -1;
    }
}
