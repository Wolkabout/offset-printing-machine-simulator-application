#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "simulator.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Simulator &simulator, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Simulator &simulator;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
