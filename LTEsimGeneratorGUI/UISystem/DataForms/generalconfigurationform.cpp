#include "generalconfigurationform.h"
#include "ui_generalconfiguration.h"
#include "Data/project.h"

#include <QMessageBox>

GeneralConfiguration::GeneralConfiguration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GeneralConfiguration)
{
    ui->setupUi(this);
}

GeneralConfiguration::~GeneralConfiguration()
{
    delete ui;
}
void GeneralConfiguration::loadAndOpen(const GeneralConfigurationParameters &generalConfigurationParameters, const QString &projectName,bool enable)
{
    this->generalConfigurationParameters = generalConfigurationParameters;
    this->projectName = projectName;
    this->setReadOnly(enable);
    this->show();
}
void GeneralConfiguration::updateUi(){
    this->ui->FileGzipEnabledCheckbox->setEnabled(this->generalConfigurationParameters.loggerFileGzipEnabled);
    this->ui->FileCountVal->setText(QString::number(generalConfigurationParameters.loggerFileCount));
    this->ui->FileSIzeLimitVal->setText(QString::number(generalConfigurationParameters.loggerFileSizeLimit.first) + "**" + QString::number(generalConfigurationParameters.loggerFileSizeLimit.second));
    this->ui->CoreParametersVal->setText(generalConfigurationParameters.coreParameters);
    this->ui->HandlerSetVal->setText(generalConfigurationParameters.loggerHandlerSet);
    this->ui->LogDirVal->setText(generalConfigurationParameters.logDir);
}
void GeneralConfiguration::getParameters(){
    generalConfigurationParameters.loggerFileGzipEnabled = (this->ui->FileGzipEnabledCheckbox->isChecked() ? true : false);
    generalConfigurationParameters.logDir = this->ui->LogDirVal->text();
    generalConfigurationParameters.coreParameters = this->ui->CoreParametersVal->text();
    generalConfigurationParameters.loggerFileCount = this->ui->FileCountVal->text().toInt();
    generalConfigurationParameters.loggerFileSizeLimit.first = this->ui->FileSIzeLimitVal->text().split("**")[0].toInt();
    generalConfigurationParameters.loggerFileSizeLimit.second = this->ui->FileSIzeLimitVal->text().split("**")[1].toInt();
}

void GeneralConfiguration::on_restoreButton_clicked()
{
    this->updateUi();
}

void GeneralConfiguration::on_okButton_clicked()
{
    this->getParameters();
    this->close();
    emit updateGeneralConfiguration(generalConfigurationParameters,projectName);
}

void GeneralConfiguration::on_cancelButton_clicked()
{
    this->close();
}
void GeneralConfiguration::setReadOnly(bool value)
{
    this->ui->FileGzipEnabledCheckbox->setEnabled(!value);
    this->ui->FileCountVal->setReadOnly(value);
    this->ui->FileSIzeLimitVal->setReadOnly(value);
    this->ui->CoreParametersVal->setReadOnly(value);
    this->ui->HandlerSetVal->setReadOnly(value);
    this->ui->LogDirVal->setReadOnly(value);
}
