#include "ratelistener.h"
#include "utility.h"

RateListener::RateListener(Conveyor& conveyor, QLabel * rateLabel)
    : conveyor(conveyor), rateLabel(rateLabel) {
    QObject::connect(this, SIGNAL(setRate(QString)), rateLabel, SLOT(setText(QString)), Qt::ConnectionType::QueuedConnection);
}

RateListener::RateListener(Conveyor& conveyor, QPushButton * button)
    : conveyor(conveyor), button(button) {
    QObject::connect(this, SIGNAL(setRate(QString)), button, SLOT(setText(QString)), Qt::ConnectionType::QueuedConnection);
}

void RateListener::ReceiveMessage(std::shared_ptr<ConveyorRateMessage> message) {
    if (button == nullptr) {
        emit setRate(Utility::replaceNumbers(rateLabel->text(), QString::number(message->getCurrentRate())));
    } else {
        emit setRate(Utility::replaceNumbers(button->text(), QString::number(message->getCurrentRate())));
    }
};
