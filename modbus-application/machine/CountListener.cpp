#include "CountListener.h"
#include "Utility.h"

#include <cmath>

CountListener::CountListener(const simulator::TempoComponent& tempoComponent, QLabel * label, QLabel *optionalLabel)
    : m_tempoComponent(tempoComponent), m_button(nullptr), m_label(label), m_optionalLabel(optionalLabel)
{
    QObject::connect(this, SIGNAL(receiveLabels(QString, QString)), this, SLOT(setLabels(QString, QString)),
                 Qt::ConnectionType::QueuedConnection);
}

CountListener::CountListener(const simulator::TempoComponent& tempoComponent, QLabel *label)
        : m_tempoComponent(tempoComponent), m_button(nullptr), m_label(label), m_optionalLabel(nullptr)
{
    QObject::connect(this, SIGNAL(receiveLabels(QString, QString)), this, SLOT(setLabels(QString, QString)),
                     Qt::ConnectionType::QueuedConnection);
}

CountListener::CountListener(const simulator::TempoComponent& tempoComponent, QPushButton *button)
        : m_tempoComponent(tempoComponent), m_button(button), m_label(nullptr), m_optionalLabel(nullptr)
{
    QObject::connect(this, SIGNAL(receiveLabels(QString, QString)), this, SLOT(setLabels(QString, QString)),
                     Qt::ConnectionType::QueuedConnection);
}

void CountListener::setLabels(QString one, QString two)
{
    if (m_button == nullptr)
    {
        if (m_optionalLabel == nullptr)
        {
            QStringList list = m_label->text().split('/');
            m_label->setText(one + '/' + two);
        }
        else
        {
            m_label->setText(Utility::replaceNumbers(m_label->text(), one));
            m_optionalLabel->setText(Utility::replaceNumbers(m_optionalLabel->text(), two));
        }
    }
    else
    {
        m_button->setText(m_button->text().split(' ')[0] + " (" + one + '/' + two + ')');
    }
}

void CountListener::ReceiveMessage(std::shared_ptr<simulator::CountMessage> message)
{
    emit receiveLabels(QString::number(message->getCount()),
                       QString::number(std::round(message->getPercentage() * 100)) + '%');
}

