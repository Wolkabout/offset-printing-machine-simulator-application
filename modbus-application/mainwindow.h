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
    MainWindow(Simulator &simulator, QWidget *parent = nullptr);
    ~MainWindow() override;
    QFrame *frameHolder();
    void windowActivationChange(bool) override;
    WindowManager& getWindowManager();

private slots:
    void on_logButton_clicked();

    void on_backButton_clicked();

    void on_homeButton_clicked();

    void on_settingsButton_clicked();

    void on_machineButton_clicked();

private:
    WindowManager windowManager;
    Simulator &simulator;
    Ui::MainWindow *ui;
    void timerEvent(QTimerEvent *event) override;
};

#endif // MAINWINDOW_H
