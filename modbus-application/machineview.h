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
public:
    MachineView(Simulator& simulator, QWidget *parent = nullptr);
    ~MachineView();

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
};

#endif // MACHINEVIEW_H
