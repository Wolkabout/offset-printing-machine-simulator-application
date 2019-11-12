#ifndef MESSAGEALERT_H
#define MESSAGEALERT_H

#include <QWidget>

namespace Ui {
class MessageAlert;
}

class MessageAlert : public QWidget
{
    Q_OBJECT

public:
    explicit MessageAlert(QString title, QString message, QWidget *parent = nullptr);
    ~MessageAlert();

private slots:
    void on_ok_clicked();

private:
    Ui::MessageAlert *ui;
};

#endif // MESSAGEALERT_H
