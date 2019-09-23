#ifndef UTILITY_H
#define UTILITY_H

#include <QHostAddress>
#include <QString>
#include <qnetworkinterface.h>
#include <regex>

class Utility {
public:
    static QString replaceNumbers(QString source, QString newNumber) {
        std::string exclusionPattern = "h2";
        std::string returningPattern = "~";
        std::string pattern = "([0-9]+\\.)?[0-9]+(\\%)?";
        std::regex exclusion(exclusionPattern);
        std::regex returning(returningPattern);
        std::regex regex(pattern);
        std::string message = source.toStdString();
        std::string result = std::regex_replace(message, exclusion, returningPattern);
        result = std::regex_replace(result, regex, newNumber.toStdString());
        result = std::regex_replace(result, returning, exclusionPattern);
        return QString::fromStdString(result);
    }
    static QString getIp() {
        const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
        QString addressString;
        for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
            if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost) {
                 addressString += address.toString();
                 break;
            }
        }
        return addressString;
    }
};

#endif // UTILITY_H
