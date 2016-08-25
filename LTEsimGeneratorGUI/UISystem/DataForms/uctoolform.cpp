#include "uctoolform.h"
#include "ui_uctoolform.h"
#include <QtDebug>


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
}

void UCtoolForm::on_buttonBox_rejected()
{
}

void UCtoolForm::on_pbReset_clicked()
{

}

void UCtoolForm::loadAndOpen(const UCToolSettings &ucToolSettings, const QString &projectName)
{
    this->ucToolSettings = ucToolSettings;
    this->projectName = projectName;
    this->setDefaultParameters();
    this->show();
}

void UCtoolForm::setDefaultParameters()
{
    this->ui->tet_uctool_ip->setText(ucToolSettings.ucToolIP);
    this->ui->tet_uctool_cIds->setText(ucToolSettings.ucToolCIds);
    this->ui->tet_uctool_service_ip->setText(ucToolSettings.ucToolServiceIp);
}
