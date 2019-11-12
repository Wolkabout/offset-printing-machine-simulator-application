#ifndef MACHINEVIEW_H
#define MACHINEVIEW_H

#include "simulator.h"

#include <QFrame>
#include <QLabel>

#include <map>

namespace Ui {
class MachineView;
}

class MachineView : public QFrame
{
    Q_OBJECT
    std::map<QLabel*, QMovie*> labels;
    Simulator& simulator;
    std::shared_ptr<ExternalMachineStateReceiver> listener;
    std::shared_ptr<CountMessageReceiver> feederListener;
    std::shared_ptr<CountMessageReceiver> cyanListener;
    std::shared_ptr<CountMessageReceiver> magentaListener;
    std::shared_ptr<CountMessageReceiver> yellowListener;
    std::shared_ptr<CountMessageReceiver> blackListener;
    std::shared_ptr<CountMessageReceiver> deliveryListener;
    std::shared_ptr<ConveyorRateMessageReceiver> conveyorListener;
    QWidget* feederWidget;
    QWidget *cyanWidget, *magentaWidget, *yellowWidget, *blackWidget;
    QWidget* deliveyWidget;
    QWidget* conveyorWidget;
public:
    MachineView(Simulator& simulator, QWidget *parent = nullptr);
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
    Ui::MachineView *ui;
};

class ViewMachineStateListener : public QObject, public ExternalMachineStateReceiver {
private:
    Q_OBJECT
    MachineView& machineView;
public:
    ViewMachineStateListener(MachineView&);
    void ReceiveMachineState(bool x) override;
signals:
    void stateChange(bool state);
};

#endif // MACHINEVIEW_H
