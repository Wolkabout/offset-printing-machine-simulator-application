#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "components/Conveyor.h"
#include "components/Delivery.h"
#include "components/Feeder.h"
#include "components/PaintStation.h"
#include "Machine.h"

#include <QWidget>

#define FEEDER_CAPACITY 17000
#define DELIVERY_CAPACITY 17000
#define PAINT_STATION_CAPACITY 10000

#define FEEDER_START_COUNT 1000
#define DELIVERY_START_COUNT 16950
#define PAINT_STATION_START_COUNT 10000

#define CONVEYOR_MAX_RATE 15000
#define CONVEYOR_START_RATE 14400

class Simulator
{
public:
    std::shared_ptr<simulator::Machine> getMachine() const;

    std::shared_ptr<simulator::Feeder> getFeeder() const;

    std::shared_ptr<simulator::PaintStation> getCyanPaint() const;

    std::shared_ptr<simulator::PaintStation> getMagentaPaint() const;

    std::shared_ptr<simulator::PaintStation> getYellowPaint() const;

    std::shared_ptr<simulator::PaintStation> getBlackPaint() const;

    std::shared_ptr<simulator::Delivery> getDelivery() const;

    std::shared_ptr<simulator::Conveyor> getConveyor() const;

    QWidget *getFeederWidget() const;

    void setFeederWidget(QWidget *value);

    QWidget *getDeliveryWidget() const;

    void setDeliveryWidget(QWidget *value);

    QWidget *getConveyorWidget() const;

    void setConveyorWidget(QWidget *value);

    QWidget *getCyanWidget() const;

    void setCyanWidget(QWidget *value);

    QWidget *getMagentaWidget() const;

    void setMagentaWidget(QWidget *value);

    QWidget *getYellowWidget() const;

    void setYellowWidget(QWidget *value);

    QWidget *getBlackWidget() const;

    void setBlackWidget(QWidget *value);

    Simulator();

private:
    std::shared_ptr<simulator::Machine> m_machine;
    std::shared_ptr<simulator::Feeder> m_feeder;
    std::shared_ptr<simulator::PaintStation> m_cyan, m_magenta, m_yellow, m_black;
    std::shared_ptr<simulator::Delivery> m_delivery;
    std::shared_ptr<simulator::Conveyor> m_conveyor;
    QWidget *m_feederWidget, *m_deliveryWidget, *m_conveyorWidget;
    QWidget *m_cyanWidget, *m_magentaWidget, *m_yellowWidget, *m_blackWidget;
};

#endif // SIMULATOR_H
