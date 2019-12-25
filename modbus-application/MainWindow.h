#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Simulator.h"
#include "WindowManager.h"

#include <QFrame>
#include <QMainWindow>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const Simulator& simulator, QWidget *parent = nullptr);

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
    void timerEvent(QTimerEvent *event) override;

    const Simulator& m_simulator;
    WindowManager m_windowManager;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
