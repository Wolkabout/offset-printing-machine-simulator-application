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

QWidget *MachineView::getFeederWidget() const
{
    return m_feederWidget;
}

QWidget *MachineView::getCyanWidget() const
{
    return m_cyanWidget;
}

QWidget *MachineView::getMagentaWidget() const
{
    return m_magentaWidget;
}

QWidget *MachineView::getYellowWidget() const
{
    return m_yellowWidget;
}

QWidget *MachineView::getBlackWidget() const
{
    return m_blackWidget;
}

QWidget *MachineView::getDeliveyWidget() const
{
    return m_deliveyWidget;
}

QWidget *MachineView::getConveyorWidget() const
{
    return m_conveyorWidget;
}

MachineView::MachineView(Simulator& simulator, QWidget *parent) :
    QFrame(parent),
    m_simulator(simulator),
    ui(new Ui::MachineView)
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

    ui->image->setPixmap(QPixmap(":/Images/Offset.svg"));
    m_animation = new QMovie(":/Images/offset_machine.gif");
    ui->image->setMovie(m_animation);
    m_animation->setScaledSize(QSize(667, 390));
    m_animation->start();
    m_animation->stop();
    m_animation->setSpeed(500);

    m_feederWidget = new FeederControl(*simulator.getFeeder(), this);
    m_cyanWidget = new PaintStationControl(*simulator.getCyanPaint(), this);
    m_magentaWidget = new PaintStationControl(*simulator.getMagentaPaint(), this);
    m_yellowWidget = new PaintStationControl(*simulator.getYellowPaint(), this);
    m_blackWidget = new PaintStationControl(*simulator.getBlackPaint(), this);
    m_deliveyWidget = new DeliveryControl(*simulator.getDelivery(), this);
    m_conveyorWidget = new ConveyorControl(*simulator.getConveyor(), this);

    m_listener = std::make_shared<ViewMachineStateListener>(*this);
    simulator.getMachine()->getExternalMachineStateReceivers().push_back(m_listener);

    ui->feederManage->setText(ui->feederManage->text().split(' ')[0] +
            " (" + QString::number(simulator.getFeeder()->getCount()) + "/" + QString::number(simulator.getFeeder()->getPercentage() * 100) + "%)");
    m_feederListener = std::make_shared<CountListener>(*(simulator.getFeeder().get()), ui->feederManage);
    simulator.getFeeder()->getCountMessageReceiver().push_back(m_feederListener);

    m_cyanListener = std::make_shared<CountListener>(*(simulator.getCyanPaint().get()), ui->cyanCount);
    simulator.getCyanPaint()->getCountMessageReceiver().push_back(m_cyanListener);

    m_magentaListener = std::make_shared<CountListener>(*(simulator.getMagentaPaint().get()), ui->magentaCount);
    simulator.getMagentaPaint()->getCountMessageReceiver().push_back(m_magentaListener);

    m_yellowListener = std::make_shared<CountListener>(*(simulator.getYellowPaint().get()), ui->yellowCount);
    simulator.getYellowPaint()->getCountMessageReceiver().push_back(m_yellowListener);

    m_blackListener = std::make_shared<CountListener>(*(simulator.getBlackPaint().get()), ui->blackCount);
    simulator.getBlackPaint()->getCountMessageReceiver().push_back(m_blackListener);

    ui->deliverManage->setText(ui->deliverManage->text().split(' ')[0] +
            " (" + QString::number(simulator.getDelivery()->getCount()) + "/" + QString::number(simulator.getDelivery()->getPercentage() * 100) + "%)");
    m_deliveryListener = std::make_shared<CountListener>(*(simulator.getDelivery().get()), ui->deliverManage);
    simulator.getDelivery()->getCountMessageReceiver().push_back(m_deliveryListener);

    ui->tempoManage->setText("Tempo " + QString::number(simulator.getConveyor()->getRatePerHour()) + " pph");
    m_conveyorListener = std::make_shared<RateListener>(*(simulator.getConveyor().get()), ui->tempoManage);
    simulator.getConveyor()->getRateMessageReceivers().push_back(m_conveyorListener);
}

ViewMachineStateListener::ViewMachineStateListener(MachineView& machineView) : m_machineView(machineView) {
    QObject::connect(this, SIGNAL(stateChange(bool)), &m_machineView, SLOT(machineStateChange(bool)), Qt::ConnectionType::QueuedConnection);
}

void ViewMachineStateListener::ReceiveMachineState(bool x) {
    emit stateChange(x);
}

void MachineView::machineStateChange(bool state) {
    if (state) {
        ui->startButton->setText("Stop");
        ui->startButton->setStyleSheet("color: #ffffff;\nborder-radius: 4px;\nbackground-color: #323232");
        m_animation->start();
    } else {
        ui->startButton->setText("Start");
        ui->startButton->setStyleSheet("color: #ffffff;\nborder-radius: 4px;\nbackground-color: #00afff");
        m_animation->stop();
    }
}

void MachineView::on_feederManage_clicked()
{
    m_feederWidget->show();
}

void MachineView::on_deliverManage_clicked()
{
    m_deliveyWidget->show();
}

void MachineView::on_cyanManage_clicked()
{
    m_cyanWidget->show();
}

void MachineView::on_magentaManage_clicked()
{
    m_magentaWidget->show();
}

void MachineView::on_yellowManage_clicked()
{
    m_yellowWidget->show();
}

void MachineView::on_blackManage_clicked()
{
    m_blackWidget->show();
}

void MachineView::on_tempoManage_clicked()
{
    m_conveyorWidget->show();
}

void MachineView::on_emergencyStop_clicked()
{
    std::shared_ptr<ComponentMessage> message = std::make_shared<ComponentMessage>(Severe, "The Emergency Button was triggered!");
    m_simulator.getMachine()->receiveMessages(message);
}

void MachineView::on_paperJam_clicked()
{
    std::shared_ptr<ComponentMessage> message = std::make_shared<ComponentMessage>(Severe, "A paper jammed the machine!");
    m_simulator.getMachine()->receiveMessages(message);
}

void MachineView::on_startButton_clicked()
{
    if (m_simulator.getMachine()->isRunning()) {
        m_simulator.getMachine()->stop();
    } else {
        m_simulator.getMachine()->start();
    }
}

MachineView::~MachineView()
{
    delete ui;
}
