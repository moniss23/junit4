#include "ipexform.h"
#include "ui_ipexform.h"

IpexForm::IpexForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ipexForm)
{
    ui->setupUi(this);
}

IpexForm::~IpexForm()
{
    delete ui;
}

void IpexForm::loadAndSpawn(const DataGeneratorSettings &dataGeneratorSettings, const QString &projectName, bool enable)
{
    this->dataGeneratorSettings = dataGeneratorSettings;
    this->projectName = projectName;
    this->updateUi();
    if(this->dataGeneratorSettings.runIpexEnvoirement) {
        this->enableWindow(this->dataGeneratorSettings.runIpexEnvoirement);
        this->setReadOnly(!enable);
    } else {
        this->setReadOnly(!enable);
        this->enableWindow(this->dataGeneratorSettings.runIpexEnvoirement);
    }
    this->setWindowFlags( Qt::Dialog | Qt::WindowStaysOnTopHint);
    this->show();
}

void IpexForm::on_pbReset_clicked()
{
    updateUi();
}

void IpexForm::getParameters()
{
    dataGeneratorSettings.dataGenerator = this->ui->tet_dataGenerator->text();
    dataGeneratorSettings.userDataGenerator = this->ui->tet_userDataGen->toPlainText().split("\n");
    dataGeneratorSettings.ipgwtg_IP_Address = this->ui->tet_ipgwtg_ipAddress->text();
    dataGeneratorSettings.ipgwtgPort = this->ui->tet_ipgwtg_port->text().toInt();
    dataGeneratorSettings.ipgwtgFtpSenderConnectPut = (this->ui->checkBox_ipgwtg_ftp_sender_connect_put->isChecked() ? true : false);
    dataGeneratorSettings.ipgwtgInbandSignaling = (this->ui->checkBox_ipgwtg_inband_signaling->isChecked() ? true : false);
    dataGeneratorSettings.startIspSimulator = (this->ui->checkBox_start_isp_simulator->isChecked() ? true : false);
    dataGeneratorSettings.runIpexEnvoirement = this->ui->RunIpexEnvoironementChbox->isChecked();
}

void IpexForm::updateUi()
{
    this->ui->tet_dataGenerator->setText(dataGeneratorSettings.dataGenerator);
    this->ui->tet_userDataGen->setText(dataGeneratorSettings.userDataGenerator.join("\n"));
    this->ui->tet_ipgwtg_ipAddress->setText(dataGeneratorSettings.ipgwtg_IP_Address);
    this->ui->tet_ipgwtg_port->setText(QString::number(dataGeneratorSettings.ipgwtgPort));
    this->ui->checkBox_ipgwtg_ftp_sender_connect_put->setChecked(dataGeneratorSettings.ipgwtgFtpSenderConnectPut);
    this->ui->checkBox_ipgwtg_inband_signaling->setChecked(dataGeneratorSettings.ipgwtgInbandSignaling);
    this->ui->checkBox_start_isp_simulator->setChecked(dataGeneratorSettings.startIspSimulator);
    this->ui->RunIpexEnvoironementChbox->setChecked(this->dataGeneratorSettings.runIpexEnvoirement);
}
void IpexForm::setReadOnly(bool value)
{
    this->ui->RunIpexEnvoironementChbox->setEnabled(value);
    this->ui->tet_dataGenerator->setEnabled(value);
    this->ui->tet_ipgwtg_ipAddress->setEnabled(value);
    this->ui->tet_ipgwtg_port->setEnabled(value);
    this->ui->tet_userDataGen->setEnabled(value);
    this->ui->checkBox_ipgwtg_ftp_sender_connect_put->setEnabled(value);
    this->ui->checkBox_ipgwtg_inband_signaling->setEnabled(value);
    this->ui->checkBox_start_isp_simulator->setEnabled(value);
    this->ui->pbReset->setEnabled(value);
    this->ui->okButton->setEnabled(value);
}

void IpexForm::on_okButton_clicked()
{
    this->getParameters();
    emit updateDataGeneratorSettings(dataGeneratorSettings, projectName);
    this->close();
}

void IpexForm::on_cancelButton_clicked()
{
    this->close();
}
void IpexForm::enableWindow(bool value)
{
    this->ui->tet_dataGenerator->setEnabled(value);
    this->ui->tet_ipgwtg_ipAddress->setEnabled(value);
    this->ui->tet_ipgwtg_port->setEnabled(value);
    this->ui->tet_userDataGen->setEnabled(value);
    this->ui->checkBox_ipgwtg_ftp_sender_connect_put->setEnabled(value);
    this->ui->checkBox_ipgwtg_inband_signaling->setEnabled(value);
    this->ui->checkBox_start_isp_simulator->setEnabled(value);
}

void IpexForm::on_RunIpexEnvoironementChbox_toggled(bool checked)
{
    this->enableWindow(checked);
    this->dataGeneratorSettings.runIpexEnvoirement=checked;
}
