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
