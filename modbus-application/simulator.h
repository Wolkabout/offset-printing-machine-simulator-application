#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <Machine.h>
#include <Components/Feeder.h>
#include <Components/PaintStation.h>
#include <Components/Delivery.h>
#include <Components/Conveyor.h>

#define FEEDER_CAPACITY 17000
#define DELIVERY_CAPACITY 17000
#define PAINT_STATION_CAPACITY 10000

#define FEEDER_START_COUNT 0
#define DELIVERY_START_COUNT 16950
#define PAINT_STATION_START_COUNT 10000

#define CONVEYOR_MAX_RATE 15000
#define CONVEYOR_START_RATE 14400

using namespace std;

class Simulator
{
private:
    shared_ptr<Machine> machine;
    shared_ptr<Feeder> feeder;
    shared_ptr<PaintStation> cyan, magenta, yellow, black;
    shared_ptr<Delivery> delivery;
    shared_ptr<Conveyor> conveyor;
public:
    shared_ptr<Machine> getMachine();

    shared_ptr<Feeder> getFeeder();

    shared_ptr<PaintStation> getCyanPaint();

    shared_ptr<PaintStation> getMagentaPaint();

    shared_ptr<PaintStation> getYellowPaint();

    shared_ptr<PaintStation> getBlackPaint();

    shared_ptr<Delivery> getDelivery();

    shared_ptr<Conveyor> getConveyor();

    Simulator();
};

#endif // SIMULATOR_H
