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
    m_simulator(simulator),
    m_thread(thread),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

    m_forms = {ui->feeder, ui->tempo, ui->delivery, ui->cyan, ui->magenta, ui->yellow, ui->black};

    thread.onReceiveConfigurations([&] (std::vector<int> values) {
        m_currentConfig = values;
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

    m_addressString = Utility::getIp();
    ui->ip->setText(m_addressString);
    m_toggled = true;
    ui->toggle->hide();

    m_currentConfig = Configurations::load();
    place(m_currentConfig);
    on_reset_clicked();
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_toggle_clicked()
{
    if (m_toggled) {
        ui->toggle->setText("Off");
        ui->toggle->setStyleSheet("\nborder-radius: 4px;\nbackground-color: #f5f5f5; color: #323232;");
        m_toggled = false;
        m_thread.exit();
    } else {
        ui->toggle->setText("On");
        ui->toggle->setStyleSheet("\nborder-radius: 4px;\nbackground-color: #00afff; color: white;");
        m_toggled = true;
        m_thread.start();
    }
}

void Settings::on_cancel_clicked()
{
    place(m_currentConfig);
}

void Settings::on_apply_clicked()
{
    auto inputs = load();
    for (int i = 0; i < Configurations::LENGTH; i++) {
        if (m_currentConfig[i] != inputs[i]) {
            // save, and change currentConfig
            Configurations::save(inputs);
            m_currentConfig = inputs;
            MessageAlert * ma = new MessageAlert("Settings", "Successfully applied!", this);
            m_thread.receiveConfigurations(inputs);
            return;
        }
    }
    MessageAlert * ma = new MessageAlert("Settings", "No changes were entered!", this);
}

void Settings::on_reset_clicked()
{
    on_cancel_clicked();
    try {
        m_simulator.getMachine()->stop();
        m_simulator.getFeeder()->setCount(m_currentConfig[0]);
        m_simulator.getConveyor()->setRatePerHour(m_currentConfig[1]);
        m_simulator.getDelivery()->setCount(m_currentConfig[2]);
        m_simulator.getCyanPaint()->setCount(m_currentConfig[3]);
        m_simulator.getMagentaPaint()->setCount(m_currentConfig[4]);
        m_simulator.getYellowPaint()->setCount(m_currentConfig[5]);
        m_simulator.getBlackPaint()->setCount(m_currentConfig[6]);
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
    for (auto form : m_forms) {
        int value = std::atoi(form->text().toStdString().c_str());
        values.push_back(value);
    }
    return values;
}

void Settings::place(std::vector<int> values)
{
    for (int i = 0; i < Configurations::LENGTH; i++) {
        m_forms[i]->setText(QString::number(values[i]));
    }
}
