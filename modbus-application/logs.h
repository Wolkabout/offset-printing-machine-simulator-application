#ifndef LOGS_H
#define LOGS_H

#include <QFrame>

namespace Ui {
class Logs;
}

class Logs : public QFrame
{
    Q_OBJECT

public:
    explicit Logs(QWidget *parent = nullptr);
    ~Logs();

private:
    Ui::Logs *ui;
};

#endif // LOGS_H
