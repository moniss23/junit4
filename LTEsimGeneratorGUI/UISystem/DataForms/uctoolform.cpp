#include "uctoolform.h"
#include "ui_uctoolform.h"

UCtoolForm::UCtoolForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UCtoolForm)
{
    ui->setupUi(this);
}

UCtoolForm::~UCtoolForm()
{
    delete ui;
}

void UCtoolForm::on_buttonBox_accepted()
{
    getParameters();
    emit updateUCToolSettings(ucToolSettings, projectName);
    this->close();
}

void UCtoolForm::on_buttonBox_rejected()
{
    this->close();
}

void UCtoolForm::on_pbReset_clicked()
{
    this->updateUi();
}

void UCtoolForm::loadAndOpen(const UCToolSettings &ucToolSettings, const QString &projectName,bool enable)
{
    this->ucToolSettings = ucToolSettings;
    this->projectName = projectName;
    this->updateUi();
    this->setReadOnly(enable);
    this->setEnabled(!enable);
    this->show();
}

void UCtoolForm::updateUi()
{
    this->ui->tet_uctool_ip->setText(ucToolSettings.ucToolIP);
    this->ui->tet_uctool_cIds->setText(ucToolSettings.ucToolCIds);
    this->ui->tet_uctool_service_ip->setText(ucToolSettings.ucToolServiceIp);
}

void UCtoolForm::getParameters()
{
    ucToolSettings.ucToolIP = this->ui->tet_uctool_ip->text();
    ucToolSettings.ucToolCIds = this->ui->tet_uctool_cIds->text();
    ucToolSettings.ucToolServiceIp = this->ui->tet_uctool_service_ip->text();
}
void UCtoolForm::setReadOnly(bool value){
    this->ui->tet_uctool_cIds->setReadOnly(value);
    this->ui->tet_uctool_ip->setReadOnly(value);
    this->ui->tet_uctool_service_ip->setReadOnly(value);
    this->ui->pbReset->setEnabled(!value);
}
