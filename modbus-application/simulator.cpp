#include "Machine/conveyorcontrol.h"
#include "Machine/deliverycontrol.h"
#include "Machine/feedercontrol.h"
#include "Machine/paintstationcontrol.h"
#include "simulator.h"

Simulator::Simulator()
{
    machine = std::make_shared<Machine>("Main Machine");
    feeder = std::make_shared<Feeder>("Feeder", *machine.get(), FEEDER_CAPACITY, FEEDER_START_COUNT);
    machine->addComponent(feeder);
    cyan = std::make_shared<PaintStation>("Cyan Paint", *machine.get(), PAINT_STATION_CAPACITY, PAINT_STATION_START_COUNT);
    machine->addComponent(cyan);
    magenta = std::make_shared<PaintStation>("Magenta Paint", *machine.get(), PAINT_STATION_CAPACITY, PAINT_STATION_START_COUNT);
    machine->addComponent(magenta);
    yellow = std::make_shared<PaintStation>("Yellow Paint", *machine.get(), PAINT_STATION_CAPACITY, PAINT_STATION_START_COUNT);
    machine->addComponent(yellow);
    black = std::make_shared<PaintStation>("Black Paint", *machine.get(), PAINT_STATION_CAPACITY, PAINT_STATION_START_COUNT);
    machine->addComponent(black);
    delivery = std::make_shared<Delivery>("Delivery", *machine.get(), DELIVERY_CAPACITY, DELIVERY_START_COUNT);
    machine->addComponent(delivery);
    conveyor = std::make_shared<Conveyor>("Conveyor Belt", *machine.get(), CONVEYOR_MAX_RATE, CONVEYOR_START_RATE);
    machine->addComponent(conveyor);
}

QWidget *Simulator::getFeederWidget() const
{
    return feederWidget;
}

void Simulator::setFeederWidget(QWidget *value)
{
    feederWidget = value;
}

QWidget *Simulator::getDeliveryWidget() const
{
    return deliveryWidget;
}

void Simulator::setDeliveryWidget(QWidget *value)
{
    deliveryWidget = value;
}

QWidget *Simulator::getConveyorWidget() const
{
    return conveyorWidget;
}

void Simulator::setConveyorWidget(QWidget *value)
{
    conveyorWidget = value;
}

QWidget *Simulator::getCyanWidget() const
{
    return cyanWidget;
}

void Simulator::setCyanWidget(QWidget *value)
{
    cyanWidget = value;
}

QWidget *Simulator::getMagentaWidget() const
{
    return magentaWidget;
}

void Simulator::setMagentaWidget(QWidget *value)
{
    magentaWidget = value;
}

QWidget *Simulator::getYellowWidget() const
{
    return yellowWidget;
}

void Simulator::setYellowWidget(QWidget *value)
{
    yellowWidget = value;
}

QWidget *Simulator::getBlackWidget() const
{
    return blackWidget;
}

void Simulator::setBlackWidget(QWidget *value)
{
    blackWidget = value;
}

shared_ptr<Machine> Simulator::getMachine()
{
    return machine;
}

shared_ptr<Feeder> Simulator::getFeeder()
{
    return feeder;
}

shared_ptr<PaintStation> Simulator::getCyanPaint()
{
    return cyan;
}

shared_ptr<PaintStation> Simulator::getMagentaPaint()
{
    return magenta;
}

shared_ptr<PaintStation> Simulator::getYellowPaint()
{
    return yellow;
}

shared_ptr<PaintStation> Simulator::getBlackPaint()
{
    return black;
}

shared_ptr<Delivery> Simulator::getDelivery()
{
    return delivery;
}

shared_ptr<Conveyor> Simulator::getConveyor()
{
    return conveyor;
}
