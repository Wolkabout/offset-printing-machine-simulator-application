#include "machineview.h"
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

    feederListener = std::make_shared<ComponentCountListener>(*this, *(simulator.getFeeder().get()), ui->feederCount);
    simulator.getFeeder()->getCountMessageReceiver().push_back(feederListener);

    cyanListener = std::make_shared<ComponentCountListener>(*this, *(simulator.getCyanPaint().get()), ui->cyanCount);
    simulator.getCyanPaint()->getCountMessageReceiver().push_back(cyanListener);

    magentaListener = std::make_shared<ComponentCountListener>(*this, *(simulator.getMagentaPaint().get()), ui->magentaCount);
    simulator.getMagentaPaint()->getCountMessageReceiver().push_back(magentaListener);

    yellowListener = std::make_shared<ComponentCountListener>(*this, *(simulator.getYellowPaint().get()), ui->yellowCount);
    simulator.getYellowPaint()->getCountMessageReceiver().push_back(yellowListener);

    blackListener = std::make_shared<ComponentCountListener>(*this, *(simulator.getBlackPaint().get()), ui->blackCount);
    simulator.getBlackPaint()->getCountMessageReceiver().push_back(blackListener);

    deliveryListener = std::make_shared<ComponentCountListener>(*this, *(simulator.getDelivery().get()), ui->deliveryCount);
    simulator.getDelivery()->getCountMessageReceiver().push_back(deliveryListener);

    conveyorListener = std::make_shared<ConveyorListener>(*this, *(simulator.getConveyor().get()), ui->tempoCount);
    simulator.getConveyor()->getRateMessageReceivers().push_back(conveyorListener);
    ui->tempoCount->setText(QString::number(simulator.getConveyor()->getRatePerHour()) + " pph");
}

MachineView::ViewMachineStateListener::ViewMachineStateListener(MachineView& machineView) : machineView(machineView) { }

void MachineView::ViewMachineStateListener::ReceiveMachineState(bool x) {
    if (x) {
        machineView.startAnimation();
    } else {
        machineView.stopAnimation();
    }
}

MachineView::ComponentCountListener::ComponentCountListener(MachineView& machineView, TempoComponent& tempoComponent, QLabel * label)
    : machineView(machineView), tempoComponent(tempoComponent), label(label) { }

void MachineView::ComponentCountListener::ReceiveMessage(std::shared_ptr<CountMessage> message) {
    QMetaObject::invokeMethod(label, "setText", Qt::QueuedConnection, Q_ARG(QString, QString::number(message->getCount()) + "/" + QString::number(message->getPercentage() * 100) + "%"));
//    this is if you want your house on fire
//    label->setText(QString::fromStdString(std::to_string(message->getCount())));
};

MachineView::ConveyorListener::ConveyorListener(MachineView& machineView, Conveyor& conveyor, QLabel * label)
    : machineView(machineView), conveyor(conveyor), label(label) { }

void MachineView::ConveyorListener::ReceiveMessage(std::shared_ptr<ConveyorRateMessage> message) {
    QMetaObject::invokeMethod(label, "setText", Qt::QueuedConnection, Q_ARG(QString, QString::number(message->getCurrentRate()) + " pph"));
};

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
