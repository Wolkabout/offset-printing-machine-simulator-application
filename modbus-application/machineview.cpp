#include "countlistener.h"
#include "deliverycontrol.h"
#include "feedercontrol.h"
#include "machineview.h"
#include "paintstationcontrol.h"
#include "ratelistener.h"
#include "ui_machineview.h"

#include <QMovie>
#include <QDebug>
#include <map>
#include <QMessageBox>
#include <QMetaObject>
#include <QFontDatabase>

MachineView::MachineView(Simulator& simulator, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::MachineView),
    simulator(simulator)
{
    ui->setupUi(this);

    // Programatically setting the font for literally everything

    QFont robotoMedium16(QFontDatabase::applicationFontFamilies(0).at(0), 12, QFont::DemiBold);
    ui->cyanManage->setFont(robotoMedium16);
    ui->magentaManage->setFont(robotoMedium16);
    ui->yellowManage->setFont(robotoMedium16);
    ui->blackManage->setFont(robotoMedium16);
    ui->feederManage->setFont(robotoMedium16);
    ui->deliverManage->setFont(robotoMedium16);
    ui->feederManage->setFont(robotoMedium16);
    ui->tempoManage->setFont(robotoMedium16);
    ui->paperJam->setFont(robotoMedium16);
    ui->emergencyStop->setFont(robotoMedium16);
    ui->startButton->setFont(robotoMedium16);
    QFont robotoMedium14(QFontDatabase::applicationFontFamilies(0).at(0), 10, QFont::DemiBold);
    ui->cyanCount->setFont(robotoMedium14);
    ui->magentaCount->setFont(robotoMedium14);
    ui->yellowCount->setFont(robotoMedium14);
    ui->blackCount->setFont(robotoMedium14);

    ui->image->setPixmap(QPixmap(":/Images/Resources/Offset.svg"));

    feederWidget = new FeederControl(*simulator.getFeeder(), this);
    cyanWidget = new PaintStationControl(*simulator.getCyanPaint(), this);
    magentaWidget = new PaintStationControl(*simulator.getMagentaPaint(), this);
    yellowWidget = new PaintStationControl(*simulator.getYellowPaint(), this);
    blackWidget = new PaintStationControl(*simulator.getBlackPaint(), this);
    deliveyWidget = new DeliveryControl(*simulator.getDelivery(), this);
    conveyorWidget = new ConveyorControl(*simulator.getConveyor(), this);

    listener = std::make_shared<ViewMachineStateListener>(*this);
    simulator.getMachine()->getExternalMachineStateReceivers().push_back(listener);

    ui->feederManage->setText(ui->feederManage->text().split(' ')[0] +
            " (" + QString::number(simulator.getFeeder()->getCount()) + "/" + QString::number(simulator.getFeeder()->getPercentage() * 100) + "%)");
    feederListener = std::make_shared<CountListener>(*(simulator.getFeeder().get()), ui->feederManage);
    simulator.getFeeder()->getCountMessageReceiver().push_back(feederListener);

    cyanListener = std::make_shared<CountListener>(*(simulator.getCyanPaint().get()), ui->cyanCount);
    simulator.getCyanPaint()->getCountMessageReceiver().push_back(cyanListener);

    magentaListener = std::make_shared<CountListener>(*(simulator.getMagentaPaint().get()), ui->magentaCount);
    simulator.getMagentaPaint()->getCountMessageReceiver().push_back(magentaListener);

    yellowListener = std::make_shared<CountListener>(*(simulator.getYellowPaint().get()), ui->yellowCount);
    simulator.getYellowPaint()->getCountMessageReceiver().push_back(yellowListener);

    blackListener = std::make_shared<CountListener>(*(simulator.getBlackPaint().get()), ui->blackCount);
    simulator.getBlackPaint()->getCountMessageReceiver().push_back(blackListener);

    ui->deliverManage->setText(ui->deliverManage->text().split(' ')[0] +
            " (" + QString::number(simulator.getDelivery()->getCount()) + "/" + QString::number(simulator.getDelivery()->getPercentage() * 100) + "%)");
    deliveryListener = std::make_shared<CountListener>(*(simulator.getDelivery().get()), ui->deliverManage);
    simulator.getDelivery()->getCountMessageReceiver().push_back(deliveryListener);

    ui->tempoManage->setText("Tempo " + QString::number(simulator.getConveyor()->getRatePerHour()) + " pph");
    conveyorListener = std::make_shared<RateListener>(*(simulator.getConveyor().get()), ui->tempoManage);
    simulator.getConveyor()->getRateMessageReceivers().push_back(conveyorListener);
}

ViewMachineStateListener::ViewMachineStateListener(MachineView& machineView) : machineView(machineView) {
    // write animation slot
//    QObject::connect(this, SIGNAL(stateChange(bool)), &machineView, SLOT(animationChange(bool)), Qt::ConnectionType::QueuedConnection);
}

void ViewMachineStateListener::ReceiveMachineState(bool x) {
    emit stateChange(x);
}

void MachineView::on_feederManage_clicked()
{
    feederWidget->show();
}

void MachineView::on_deliverManage_clicked()
{
    deliveyWidget->show();
}

void MachineView::on_cyanManage_clicked()
{
    cyanWidget->show();
}

void MachineView::on_magentaManage_clicked()
{
    magentaWidget->show();
}

void MachineView::on_yellowManage_clicked()
{
    yellowWidget->show();
}

void MachineView::on_blackManage_clicked()
{
    blackWidget->show();
}

void MachineView::on_tempoManage_clicked()
{
    conveyorWidget->show();
}

void MachineView::on_emergencyStop_clicked()
{
    std::shared_ptr<ComponentMessage> message = std::make_shared<ComponentMessage>(Severe, "The Emergency Button was triggered!");
    simulator.getMachine()->receiveMessages(message);
}

void MachineView::on_paperJam_clicked()
{
    std::shared_ptr<ComponentMessage> message = std::make_shared<ComponentMessage>(Severe, "A paper jammed the machine!");
    simulator.getMachine()->receiveMessages(message);
}

MachineView::~MachineView()
{
    delete ui;
}

