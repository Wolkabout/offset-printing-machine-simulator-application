#ifndef RATELISTENER_H
#define RATELISTENER_H

#include "conveyorcontrol.h"
#include <regex>
#include <QObject>
#include <QPushButton>
#include <Interfaces/ConveyorRateMessageReceiver.h>

class RateListener : public QObject, public ConveyorRateMessageReceiver {
private:
    Q_OBJECT
    Conveyor& conveyor;
    QLabel * rateLabel;
    QPushButton * button;
public:
    RateListener(Conveyor&, QLabel *);
    RateListener(Conveyor&, QPushButton *);
    void ReceiveMessage(std::shared_ptr<ConveyorRateMessage>) override;
signals:
    void setRate(QString);
};

#endif // RATELISTENER_H
