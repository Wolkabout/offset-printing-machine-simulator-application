#include "conveyorcontrol.h"
#include "deliverycontrol.h"
#include "feedercontrol.h"
#include "paintstationcontrol.h"
#include "simulator.h"

Simulator::Simulator()
{
    machine = std::make_shared<Machine>("Main Machine");
    feeder = std::make_shared<Feeder>("Feeder", *machine.get(), FEEDER_CAPACITY, FEEDER_START_COUNT);
    machine->addComponent(feeder);
    feederWidget = new FeederControl(*feeder.get());
    cyan = std::make_shared<PaintStation>("Cyan Paint", *machine.get(), PAINT_STATION_CAPACITY, PAINT_STATION_START_COUNT);
    machine->addComponent(cyan);
    cyanWidget = new PaintStationControl(*cyan.get());
    magenta = std::make_shared<PaintStation>("Magenta Paint", *machine.get(), PAINT_STATION_CAPACITY, PAINT_STATION_START_COUNT);
    machine->addComponent(magenta);
    magentaWidget = new PaintStationControl(*magenta.get());
    yellow = std::make_shared<PaintStation>("Yellow Paint", *machine.get(), PAINT_STATION_CAPACITY, PAINT_STATION_START_COUNT);
    machine->addComponent(yellow);
    yellowWidget = new PaintStationControl(*yellow.get());
    black = std::make_shared<PaintStation>("Black Paint", *machine.get(), PAINT_STATION_CAPACITY, PAINT_STATION_START_COUNT);
    machine->addComponent(black);
    blackWidget = new PaintStationControl(*black.get());
    delivery = std::make_shared<Delivery>("Delivery", *machine.get(), DELIVERY_CAPACITY, DELIVERY_START_COUNT);
    machine->addComponent(delivery);
    deliveyWidget = new DeliveryControl(*delivery.get());
    conveyor = std::make_shared<Conveyor>("Conveyor Belt", *machine.get(), CONVEYOR_MAX_RATE, CONVEYOR_START_RATE);
    machine->addComponent(conveyor);
    conveyorWidget = new ConveyorControl(*conveyor.get());
}

QWidget *Simulator::getMachineWidget() const
{
    return machineWidget;
}

QWidget *Simulator::getFeederWidget() const
{
    return feederWidget;
}

QWidget *Simulator::getCyanWidget() const
{
    return cyanWidget;
}

QWidget *Simulator::getMagentaWidget() const
{
    return magentaWidget;
}

QWidget *Simulator::getYellowWidget() const
{
    return yellowWidget;
}

QWidget *Simulator::getBlackWidget() const
{
    return blackWidget;
}

QWidget *Simulator::getDeliveyWidget() const
{
    return deliveyWidget;
}

QWidget *Simulator::getConveyorWidget() const
{
    return conveyorWidget;
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
