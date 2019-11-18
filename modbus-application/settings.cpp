#include <QFontDatabase>
#include <QMessageBox>
#include <QNetworkInterface>
#include "messagealert.h"
#include "settings.h"
#include "ui_settings.h"
#include "utility.h"
#include <modbus/modbus.h>
#include <modbus/modbus-tcp.h>

Settings::Settings(Simulator& simulator, ModbusThread &thread, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Settings),
    simulator(simulator),
    thread(thread)
{
    ui->setupUi(this);

    forms = {ui->feeder, ui->tempo, ui->delivery, ui->cyan, ui->magenta, ui->yellow, ui->black};

    thread.onReceiveConfigurations([&] (std::vector<int> values) {
        currentConfig = values;
        place(values);
        Configurations::save(values);
    });

    if (!Configurations::exists()) {
        // These are default values
        Configurations::save({17000, 14400, 0, 10000, 10000, 10000, 10000});
    }

    QFont robotoBold18(QFontDatabase::applicationFontFamilies(2).at(0), 14, QFont::DemiBold);
    ui->title->setFont(robotoBold18);
    ui->title_2->setFont(robotoBold18);
    QFont robotoMedium14(QFontDatabase::applicationFontFamilies(0).at(0), 10, QFont::DemiBold);
    ui->ip_title->setFont(robotoMedium14);
    ui->label->setFont(robotoMedium14);
    ui->label_2->setFont(robotoMedium14);
    ui->label_3->setFont(robotoMedium14);
    ui->label_4->setFont(robotoMedium14);
    ui->label_5->setFont(robotoMedium14);
    ui->label_6->setFont(robotoMedium14);
    ui->label_7->setFont(robotoMedium14);
    ui->toggle->setFont(robotoMedium14);
    QFont robotoMedium16(QFontDatabase::applicationFontFamilies(0).at(0), 12, QFont::DemiBold);
    ui->feeder->setFont(robotoMedium16);
    ui->tempo->setFont(robotoMedium16);
    ui->delivery->setFont(robotoMedium16);
    ui->cyan->setFont(robotoMedium16);
    ui->magenta->setFont(robotoMedium16);
    ui->yellow->setFont(robotoMedium16);
    ui->black->setFont(robotoMedium16);
    ui->cancel->setFont(robotoMedium16);
    ui->apply->setFont(robotoMedium16);
    ui->reset->setFont(robotoMedium16);
    QFont robotoMedium18(QFontDatabase::applicationFontFamilies(0).at(0), 14, QFont::DemiBold);
    ui->ip->setFont(robotoMedium18);
    QFont robotoRegular14(QFontDatabase::applicationFontFamilies(1).at(0), 10);
    ui->desc->setFont(robotoRegular14);
    ui->desc_2->setFont(robotoRegular14);

    addressString = Utility::getIp();
    ui->ip->setText(addressString);
    toggled = true;

    currentConfig = Configurations::load();
    place(currentConfig);
    on_reset_clicked();
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_toggle_clicked()
{
    if (toggled) {
        ui->toggle->setText("Off");
        ui->toggle->setStyleSheet("\nborder-radius: 4px;\nbackground-color: #f5f5f5; color: #323232;");
        toggled = false;
        thread.exit();
    } else {
        ui->toggle->setText("On");
        ui->toggle->setStyleSheet("\nborder-radius: 4px;\nbackground-color: #00afff; color: white;");
        toggled = true;
        thread.start();
    }
}

void Settings::on_cancel_clicked()
{
    place(currentConfig);
}

void Settings::on_apply_clicked()
{
    auto inputs = load();
    for (int i = 0; i < Configurations::LENGTH; i++) {
        if (currentConfig[i] != inputs[i]) {
            // save, and change currentConfig
            Configurations::save(inputs);
            currentConfig = inputs;
            MessageAlert * ma = new MessageAlert("Settings", "Successfully applied!", this);
            thread.receiveConfigurations(inputs);
            return;
        }
    }
    MessageAlert * ma = new MessageAlert("Settings", "No changes were entered!", this);
}

void Settings::on_reset_clicked()
{
    on_cancel_clicked();
    try {
        simulator.getMachine()->stop();
        simulator.getFeeder()->setCount(currentConfig[0]);
        simulator.getConveyor()->setRatePerHour(currentConfig[1]);
        simulator.getDelivery()->setCount(currentConfig[2]);
        simulator.getCyanPaint()->setCount(currentConfig[3]);
        simulator.getMagentaPaint()->setCount(currentConfig[4]);
        simulator.getYellowPaint()->setCount(currentConfig[5]);
        simulator.getBlackPaint()->setCount(currentConfig[6]);
    } catch (std::exception &e) {
        MessageAlert * ma = new MessageAlert("Settings", "Your configuration is invalid!");
        return;
    }

    static int i = 0;
    if (i++ > 0) {
        MessageAlert * ma = new MessageAlert("Settings", "Reset to default values!", this);
    }
}

std::vector<int> Settings::load()
{
    std::vector<int> values;
    for (auto form : forms) {
        int value = std::atoi(form->text().toStdString().c_str());
        values.push_back(value);
    }
    return values;
}

void Settings::place(std::vector<int> values)
{
    for (int i = 0; i < Configurations::LENGTH; i++) {
        forms[i]->setText(QString::number(values[i]));
    }
}
