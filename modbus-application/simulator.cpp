#include "simulator.h"

Simulator::Simulator()
{
    machine = std::make_shared<Machine>("Main Machine");
    feeder = std::make_shared<Feeder>("Feeder", *machine.get(), FEEDER_CAPACITY, FEEDER_START_COUNT);
    cyan = std::make_shared<PaintStation>("Cyan Paint", *machine.get(), PAINT_STATION_CAPACITY, PAINT_STATION_START_COUNT);
    magenta = std::make_shared<PaintStation>("Magenta Paint", *machine.get(), PAINT_STATION_CAPACITY, PAINT_STATION_START_COUNT);
    yellow = std::make_shared<PaintStation>("Yellow Paint", *machine.get(), PAINT_STATION_CAPACITY, PAINT_STATION_START_COUNT);
    black = std::make_shared<PaintStation>("Black Paint", *machine.get(), PAINT_STATION_CAPACITY, PAINT_STATION_START_COUNT);
    delivery = std::make_shared<Delivery>("Delivery", *machine.get(), DELIVERY_CAPACITY, DELIVERY_START_COUNT);
    conveyor = std::make_shared<Conveyor>("Conveyor Belt", *machine.get(), CONVEYOR_MAX_RATE, CONVEYOR_START_RATE);
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
