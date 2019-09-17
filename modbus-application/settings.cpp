#include "settings.h"
#include "ui_settings.h"

Settings::Settings(Simulator& simulator, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Settings),
    simulator(simulator)
{
    ui->setupUi(this);
}

Settings::~Settings()
{
    delete ui;
}
