#include "countlistener.h"
#include "utility.h"
#include <math.h>

CountListener::CountListener(TempoComponent& tempoComponent, QLabel * label, QLabel * optionalLabel)
    : m_tempoComponent(tempoComponent), m_label(label), m_optionalLabel(optionalLabel), m_button(nullptr) {
    QObject::connect(this, SIGNAL(receiveLabels(QString, QString)), this, SLOT(setLabels(QString, QString)), Qt::ConnectionType::QueuedConnection);
}

CountListener::CountListener(TempoComponent& tempoComponent, QLabel * label)
    : m_tempoComponent(tempoComponent), m_label(label), m_optionalLabel(nullptr), m_button(nullptr) {
    QObject::connect(this, SIGNAL(receiveLabels(QString, QString)), this, SLOT(setLabels(QString, QString)), Qt::ConnectionType::QueuedConnection);
}

CountListener::CountListener(TempoComponent& tempoComponent, QPushButton * button)
    : m_tempoComponent(tempoComponent), m_label(nullptr), m_optionalLabel(nullptr), m_button(button) {
    QObject::connect(this, SIGNAL(receiveLabels(QString, QString)), this, SLOT(setLabels(QString, QString)), Qt::ConnectionType::QueuedConnection);
}

void CountListener::setLabels(QString one, QString two)
{
    if (m_button == nullptr) {
        if (m_optionalLabel == nullptr) {
            QStringList list = m_label->text().split('/');
            m_label->setText(one + '/' + two);
        } else {
            m_label->setText(Utility::replaceNumbers(m_label->text(), one));
            m_optionalLabel->setText(Utility::replaceNumbers(m_optionalLabel->text(), two));
        }
    } else {
        m_button->setText(m_button->text().split(' ')[0] + " (" + one + '/' + two + ')');
    }
}

void CountListener::ReceiveMessage(std::shared_ptr<CountMessage> message) {
    emit receiveLabels(QString::number(message->getCount()), QString::number(std::round(message->getPercentage() * 100)) + '%');
}

