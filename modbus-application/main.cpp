#include "logs.h"
#include "machineview.h"
#include "mainwindow.h"
#include "settings.h"
#include "simulator.h"
#include "windowmanager.h"
#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    try {
        QApplication a(argc, argv);

        Simulator simulator;

        QFontDatabase::addApplicationFont(":/Fonts/Resources/Roboto-Medium.ttf"); // id 0
        QFontDatabase::addApplicationFont(":/Fonts/Resources/Roboto-Regular.ttf"); // id 1
        QFontDatabase::addApplicationFont(":/Fonts/Resources/Roboto-Bold.ttf"); // id 2

        MainWindow w(simulator);
        w.show();

        ModbusThread modbusThread(simulator);
        WindowManager& windowManager = w.getWindowManager();

        QFrame * parent = w.frameHolder();
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
        modbusThread.exit();
        return res;
    } catch (std::exception &e) {
        qDebug("%s", e.what());
        return -1;
    }
}
