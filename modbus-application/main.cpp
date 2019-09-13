#include "mainwindow.h"
#include "simulator.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Simulator simulator;
    MainWindow w(simulator);
    w.show();

    return a.exec();
}
