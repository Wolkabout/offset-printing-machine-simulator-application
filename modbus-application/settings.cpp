#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
}

Settings::~Settings()
{
    delete ui;
}
