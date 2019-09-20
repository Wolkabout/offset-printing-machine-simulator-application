#include "ratelistener.h"
#include "utility.h"

RateListener::RateListener(Conveyor& conveyor, QLabel * rateLabel)
    : conveyor(conveyor), rateLabel(rateLabel) {
    QObject::connect(this, SIGNAL(setRate(QString)), rateLabel, SLOT(setText(QString)), Qt::ConnectionType::QueuedConnection);
}

void RateListener::ReceiveMessage(std::shared_ptr<ConveyorRateMessage> message) {
    emit setRate(Utility::replaceNumbers(rateLabel->text(),QString::number(message->getCurrentRate())));
};
