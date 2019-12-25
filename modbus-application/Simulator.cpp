#include "machine/ConveyorControl.h"
#include "machine/DeliveryControl.h"
#include "machine/FeederControl.h"
#include "machine/PaintStationControl.h"
#include "Simulator.h"

Simulator::Simulator()
{
    m_machine = std::make_shared<simulator::Machine>("Main Machine");
    m_feeder = std::make_shared<simulator::Feeder>("Feeder", *m_machine.get(), FEEDER_CAPACITY, FEEDER_START_COUNT);
    m_machine->addComponent(m_feeder);
    m_cyan = std::make_shared<simulator::PaintStation>("Cyan Paint", *m_machine.get(), PAINT_STATION_CAPACITY,
                                          PAINT_STATION_START_COUNT);
    m_machine->addComponent(m_cyan);
    m_magenta = std::make_shared<simulator::PaintStation>("Magenta Paint", *m_machine.get(), PAINT_STATION_CAPACITY,
                                             PAINT_STATION_START_COUNT);
    m_machine->addComponent(m_magenta);
    m_yellow = std::make_shared<simulator::PaintStation>("Yellow Paint", *m_machine.get(), PAINT_STATION_CAPACITY,
                                            PAINT_STATION_START_COUNT);
    m_machine->addComponent(m_yellow);
    m_black = std::make_shared<simulator::PaintStation>("Black Paint", *m_machine.get(), PAINT_STATION_CAPACITY,
                                           PAINT_STATION_START_COUNT);
    m_machine->addComponent(m_black);
    m_delivery = std::make_shared<simulator::Delivery>
            ("Delivery", *m_machine.get(), DELIVERY_CAPACITY, DELIVERY_START_COUNT);
    m_machine->addComponent(m_delivery);
    m_conveyor = std::make_shared<simulator::Conveyor>
            ("Conveyor Belt", *m_machine.get(), CONVEYOR_MAX_RATE, CONVEYOR_START_RATE);
    m_machine->addComponent(m_conveyor);
}

std::shared_ptr<simulator::Machine> Simulator::getMachine() const
{
    return m_machine;
}

std::shared_ptr<simulator::Feeder> Simulator::getFeeder() const
{
    return m_feeder;
}

std::shared_ptr<simulator::PaintStation> Simulator::getCyanPaint() const
{
    return m_cyan;
}

std::shared_ptr<simulator::PaintStation> Simulator::getMagentaPaint() const
{
    return m_magenta;
}

std::shared_ptr<simulator::PaintStation> Simulator::getYellowPaint() const
{
    return m_yellow;
}

std::shared_ptr<simulator::PaintStation> Simulator::getBlackPaint() const
{
    return m_black;
}

std::shared_ptr<simulator::Delivery> Simulator::getDelivery() const
{
    return m_delivery;
}

std::shared_ptr<simulator::Conveyor> Simulator::getConveyor() const
{
    return m_conveyor;
}

QWidget *Simulator::getFeederWidget() const
{
    return m_feederWidget;
}

void Simulator::setFeederWidget(QWidget *value)
{
    m_feederWidget = value;
}

QWidget *Simulator::getDeliveryWidget() const
{
    return m_deliveryWidget;
}

void Simulator::setDeliveryWidget(QWidget *value)
{
    m_deliveryWidget = value;
}

QWidget *Simulator::getConveyorWidget() const
{
    return m_conveyorWidget;
}

void Simulator::setConveyorWidget(QWidget *value)
{
    m_conveyorWidget = value;
}

QWidget *Simulator::getCyanWidget() const
{
    return m_cyanWidget;
}

void Simulator::setCyanWidget(QWidget *value)
{
    m_cyanWidget = value;
}

QWidget *Simulator::getMagentaWidget() const
{
    return m_magentaWidget;
}

void Simulator::setMagentaWidget(QWidget *value)
{
    m_magentaWidget = value;
}

QWidget *Simulator::getYellowWidget() const
{
    return m_yellowWidget;
}

void Simulator::setYellowWidget(QWidget *value)
{
    m_yellowWidget = value;
}

QWidget *Simulator::getBlackWidget() const
{
    return m_blackWidget;
}

void Simulator::setBlackWidget(QWidget *value)
{
    m_blackWidget = value;
}
