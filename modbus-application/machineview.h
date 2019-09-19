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
public:
    MachineView(Simulator& simulator, QWidget *parent = nullptr);
    ~MachineView();

private slots:
    void on_feederManage_clicked();

    void on_deliverManage_clicked();

    void on_cyanManage_clicked();

    void on_magentaManage_clicked();

    void on_yellowManage_clicked();

    void on_blackManage_clicked();

private:
    Ui::MachineView *ui;
    void startAnimation();
    void stopAnimation();
    class ViewMachineStateListener : public ExternalMachineStateReceiver {
    private:
        MachineView& machineView;
    public:
        ViewMachineStateListener(MachineView&);
        void ReceiveMachineState(bool x) override;
    };

    class ComponentCountListener : public CountMessageReceiver {
    private:
        MachineView& machineView;
        TempoComponent& tempoComponent;
        QLabel * label;
    public:
        ComponentCountListener(MachineView&, TempoComponent&, QLabel *);
        void ReceiveMessage(std::shared_ptr<CountMessage>) override;
    };
};

#endif // MACHINEVIEW_H
