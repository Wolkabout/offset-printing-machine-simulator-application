#include "machineview.h"
#include "ui_machineview.h"

#include <QMovie>
#include <QDebug>
#include <map>

MachineView::MachineView(Simulator& simulator, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::MachineView),
    simulator(simulator)
{
    ui->setupUi(this);

    labels = std::map<QLabel*, QMovie*> {
            {ui->feeder, new QMovie(":/Animations/Resources/FeederAnimation1.gif")},
            {ui->cyan, new QMovie(":/Animations/Resources/PaintStationAnimationC1.gif")},
            {ui->magenta, new QMovie(":/Animations/Resources/PaintStationAnimationM1.gif")},
            {ui->yellow, new QMovie(":/Animations/Resources/PaintStationAnimationY1.gif")},
            {ui->black, new QMovie(":/Animations/Resources/PaintStationAnimationK1.gif")},
            {ui->delivery, new QMovie(":/Animations/Resources/DeliveryAnimation1.gif")}
    };

    for (auto const& x : labels) {
        x.first->setMovie(x.second);
    }

    startAnimation();
    stopAnimation();

    listener = std::make_shared<ViewMachineStateListener>(*this);
    simulator.getMachine()->getExternalMachineStateReceivers().push_back(listener);
}

MachineView::ViewMachineStateListener::ViewMachineStateListener(MachineView& machineView) : machineView(machineView) { }

void MachineView::ViewMachineStateListener::ReceiveMachineState(bool x) {
    if (x) {
        machineView.startAnimation();
    } else {
        machineView.stopAnimation();
    }
}

void MachineView::startAnimation()
{
    for (auto const& x : labels) {
        x.second->start();
    }
}

void MachineView::stopAnimation()
{
    for (auto const& x : labels) {
        x.second->stop();
    }
}

MachineView::~MachineView()
{
    delete ui;
}
