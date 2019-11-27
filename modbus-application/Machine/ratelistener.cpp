#include "ratelistener.h"
#include "utility.h"

RateListener::RateListener(Conveyor& conveyor, QLabel * rateLabel)
    : conveyor(conveyor), rateLabel(rateLabel), button(nullptr), lineEdit(nullptr) {
    QObject::connect(this, SIGNAL(setRate(QString)), rateLabel, SLOT(setText(QString)), Qt::ConnectionType::QueuedConnection);
}

RateListener::RateListener(Conveyor & conveyor, QLineEdit * lineEdit)
    : conveyor(conveyor), rateLabel(nullptr), button(nullptr), lineEdit(lineEdit) {
    QObject::connect(this, SIGNAL(setRate(QString)), lineEdit, SLOT(setText(QString)), Qt::ConnectionType::QueuedConnection);
}

RateListener::RateListener(Conveyor& conveyor, QPushButton * button)
    : conveyor(conveyor), rateLabel(nullptr), button(button), lineEdit(nullptr) {
    QObject::connect(this, SIGNAL(setRate(QString)), this, SLOT(setButtonLabel(QString)), Qt::ConnectionType::QueuedConnection);
}

void RateListener::setButtonLabel(QString text)
{
    if (button != nullptr) {
        button->setText(text);
    }
}

void RateListener::ReceiveMessage(std::shared_ptr<ConveyorRateMessage> message) {
    if (rateLabel != nullptr) {
        emit setRate(Utility::replaceNumbers(rateLabel->text(), QString::number(message->getCurrentRate())));
    } else if (lineEdit != nullptr) {
        emit setRate(Utility::replaceNumbers(lineEdit->text(), QString::number(message->getCurrentRate())));
    } else if (button != nullptr) {
        emit setRate(Utility::replaceNumbers(button->text(), QString::number(message->getCurrentRate())));
    }
};
