#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "simulator.h"
#include "windowmanager.h"
#include <QMainWindow>
#include <QFrame>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(Simulator &simulator, WindowManager &windowManager, QWidget *parent = nullptr);
    ~MainWindow() override;
    QFrame *frameHolder();

private slots:
    void on_logButton_clicked();

    void on_backButton_clicked();

    void on_homeButton_clicked();

    void on_settingsButton_clicked();

    void on_machineButton_clicked();

private:
    Simulator &simulator;
    WindowManager &windowManager;
    Ui::MainWindow *ui;
    void timerEvent(QTimerEvent *event) override;

    class MainViewStateListener : public ExternalMachineStateReceiver {
    private:
        MainWindow& mainWindow;
    public:
        MainViewStateListener(MainWindow&);
        void ReceiveMachineState(bool) override;
    };
};

#endif // MAINWINDOW_H
