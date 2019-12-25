#include "RateListener.h"
#include "Utility.h"

RateListener::RateListener(const simulator::Conveyor& conveyor, QLabel *rateLabel)
        : m_conveyor(conveyor), m_rateLabel(rateLabel), m_button(nullptr), m_lineEdit(nullptr)
{
    QObject::connect(this, SIGNAL(setRate(QString)), rateLabel, SLOT(setText(QString)),
                     Qt::ConnectionType::QueuedConnection);
}

RateListener::RateListener(const simulator::Conveyor& conveyor, QLineEdit *lineEdit)
        : m_conveyor(conveyor), m_rateLabel(nullptr), m_button(nullptr), m_lineEdit(lineEdit)
{
    QObject::connect(this, SIGNAL(setRate(QString)), lineEdit, SLOT(setText(QString)),
                     Qt::ConnectionType::QueuedConnection);
}

RateListener::RateListener(const simulator::Conveyor& conveyor, QPushButton *button)
        : m_conveyor(conveyor), m_rateLabel(nullptr), m_button(button), m_lineEdit(nullptr)
{
    QObject::connect(this, SIGNAL(setRate(QString)), this, SLOT(setButtonLabel(QString)),
                     Qt::ConnectionType::QueuedConnection);
}

void RateListener::setButtonLabel(QString text)
{
    if (m_button != nullptr)
    {
        m_button->setText(text);
    }
}

void RateListener::ReceiveMessage(std::shared_ptr<simulator::ConveyorRateMessage> message)
{
    if (m_rateLabel != nullptr)
    {
        emit setRate(Utility::replaceNumbers(m_rateLabel->text(), QString::number(message->getCurrentRate())));
    }
    else if (m_lineEdit != nullptr)
    {
        emit setRate(Utility::replaceNumbers(m_lineEdit->text(), QString::number(message->getCurrentRate())));
    }
    else if (m_button != nullptr)
    {
        emit setRate(Utility::replaceNumbers(m_button->text(), QString::number(message->getCurrentRate())));
    }
}
