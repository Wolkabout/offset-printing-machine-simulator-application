#include "countlistener.h"
#include "machineview.h"
#include "ratelistener.h"
#include "ui_machineview.h"

#include <QMovie>
#include <QDebug>
#include <map>
#include <QMessageBox>
#include <QMetaObject>

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

    feederListener = std::make_shared<CountListener>(*(simulator.getFeeder().get()), ui->feederCount);
    simulator.getFeeder()->getCountMessageReceiver().push_back(feederListener);

    cyanListener = std::make_shared<CountListener>(*(simulator.getCyanPaint().get()), ui->cyanCount);
    simulator.getCyanPaint()->getCountMessageReceiver().push_back(cyanListener);

    magentaListener = std::make_shared<CountListener>(*(simulator.getMagentaPaint().get()), ui->magentaCount);
    simulator.getMagentaPaint()->getCountMessageReceiver().push_back(magentaListener);

    yellowListener = std::make_shared<CountListener>(*(simulator.getYellowPaint().get()), ui->yellowCount);
    simulator.getYellowPaint()->getCountMessageReceiver().push_back(yellowListener);

    blackListener = std::make_shared<CountListener>(*(simulator.getBlackPaint().get()), ui->blackCount);
    simulator.getBlackPaint()->getCountMessageReceiver().push_back(blackListener);

    deliveryListener = std::make_shared<CountListener>(*(simulator.getDelivery().get()), ui->deliveryCount);
    simulator.getDelivery()->getCountMessageReceiver().push_back(deliveryListener);

    ui->tempoCount->setText(QString::number(simulator.getConveyor()->getRatePerHour()) + " pph");
    conveyorListener = std::make_shared<RateListener>(*(simulator.getConveyor().get()), ui->tempoCount);
    simulator.getConveyor()->getRateMessageReceivers().push_back(conveyorListener);
}

ViewMachineStateListener::ViewMachineStateListener(MachineView& machineView) : machineView(machineView) {
    QObject::connect(this, SIGNAL(stateChange(bool)), &machineView, SLOT(animationChange(bool)), Qt::ConnectionType::QueuedConnection);
}

void ViewMachineStateListener::ReceiveMachineState(bool x) {
    emit stateChange(x);
}

void MachineView::animationChange(bool state) {
    if (state) {
        startAnimation();
    } else {
        stopAnimation();
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

void MachineView::on_feederManage_clicked()
{
    simulator.getFeederWidget()->show();
}

void MachineView::on_deliverManage_clicked()
{
    simulator.getDeliveyWidget()->show();
}

void MachineView::on_cyanManage_clicked()
{
    simulator.getCyanWidget()->show();
}

void MachineView::on_magentaManage_clicked()
{
    simulator.getMagentaWidget()->show();
}

void MachineView::on_yellowManage_clicked()
{
    simulator.getYellowWidget()->show();
}

void MachineView::on_blackManage_clicked()
{
    simulator.getBlackWidget()->show();
}

void MachineView::on_tempoManage_clicked()
{
    simulator.getConveyorWidget()->show();
}

MachineView::~MachineView()
{
    delete ui;
}
