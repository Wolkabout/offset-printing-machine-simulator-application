#ifndef MACHINEVIEW_H
#define MACHINEVIEW_H

#include "Simulator.h"

#include <QFrame>
#include <QLabel>

namespace Ui
{
    class MachineView;
}

class MachineView : public QFrame
{
    Q_OBJECT
public:
    MachineView(const Simulator& simulator, QWidget *parent = nullptr);

    ~MachineView();

    QWidget *getFeederWidget() const;

    QWidget *getCyanWidget() const;

    QWidget *getMagentaWidget() const;

    QWidget *getYellowWidget() const;

    QWidget *getBlackWidget() const;

    QWidget *getDeliveyWidget() const;

    QWidget *getConveyorWidget() const;

public slots:
    void machineStateChange(bool);

private slots:
    void on_feederManage_clicked();

    void on_deliverManage_clicked();

    void on_cyanManage_clicked();

    void on_magentaManage_clicked();

    void on_yellowManage_clicked();

    void on_blackManage_clicked();

    void on_tempoManage_clicked();

    void on_paperJam_clicked();

    void on_emergencyStop_clicked();

    void on_startButton_clicked();

private:
    const Simulator& m_simulator;
    std::shared_ptr<simulator::ExternalMachineStateReceiver> m_listener;
    std::shared_ptr<simulator::CountMessageReceiver> m_feederListener;
    std::shared_ptr<simulator::CountMessageReceiver> m_cyanListener;
    std::shared_ptr<simulator::CountMessageReceiver> m_magentaListener;
    std::shared_ptr<simulator::CountMessageReceiver> m_yellowListener;
    std::shared_ptr<simulator::CountMessageReceiver> m_blackListener;
    std::shared_ptr<simulator::CountMessageReceiver> m_deliveryListener;
    std::shared_ptr<simulator::ConveyorRateMessageReceiver> m_conveyorListener;
    // Keeping consistency with QT, QWidgets are raw pointers
    QWidget *m_feederWidget;
    QWidget *m_cyanWidget, *m_magentaWidget, *m_yellowWidget, *m_blackWidget;
    QWidget *m_deliveyWidget;
    QWidget *m_conveyorWidget;
    QMovie *m_animation;
    Ui::MachineView *ui;
};

class ViewMachineStateListener : public QObject, public simulator::ExternalMachineStateReceiver
{
    Q_OBJECT
public:
    ViewMachineStateListener(MachineView&);

    void ReceiveMachineState(bool x) override;

signals:
    void stateChange(bool state);

private:
    MachineView& m_machineView;
};

#endif // MACHINEVIEW_H
