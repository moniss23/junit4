#include <QRegExp>
#include <QPair>

#include "sgwform.h"
#include "ui_sgwform.h"

SgwForm::SgwForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SGWForm)
{
    ui->setupUi(this);
    this->setWindowTitle("SGW settings");
    //set tooltips for lbls
    this->ui->lblSgw_names->setToolTip("Name of the Serving GWs e.g. \"sgw1\"");
    this->ui->lblSgw_ipAddresses->setToolTip("e.g. \"127.0.0.1\" ");
    this->ui->lblSgw_apn_list->setToolTip("The parameter contains APN name and an IP number range tjat the SGW will assign to the UE e.g. \"ltesim-core-network,172.17.0.1/16;\"");
    this->ui->lblSgw_LDIs->setToolTip("e.g. \"30\"");
}

SgwForm::~SgwForm()
{
    delete ui;
}
void SgwForm::on_buttonBox_accepted()
{
    setChanges();
    this->close();
}
void SgwForm::on_buttonBox_rejected()
{
    this->close();
}

void SgwForm::on_pbReset_clicked()
{
    updateUi();
}

void SgwForm::setChanges()
{
    if(ui->tet_sgw_names->text() != sgwSettings.name) {
        sgwSettings.name=this->ui->tet_sgw_names->text();
    }
    if(ui->tet_sgw_ipAddresses->text() != sgwSettings.ipAdress) {
        sgwSettings.ipAdress=this->ui->tet_sgw_ipAddresses->text();
    }
    else if(ui->tet_sgw_LDIs->text() != QString::number(sgwSettings.ldi)) {
        sgwSettings.ldi = ui->tet_sgw_LDIs->text().toInt();
    }
    QRegExp separator("(,|:)");
    QStringList apnListToSave = (ui->tet_sgw_apn_lists->text()).split(separator,QString::SkipEmptyParts);
    sgwSettings.apnList.clear();
    for (int i=0;i<apnListToSave.size();i+=2){
        sgwSettings.apnList = this->ui->tet_sgw_apn_lists->text();
    }
    emit updateSgw(sgwSettings,projectName);
}
void SgwForm::updateUi(){
    this->ui->tet_sgw_names->setText(sgwSettings.name);
    this->ui->tet_sgw_ipAddresses->setText(sgwSettings.ipAdress);
    this->ui->tet_sgw_LDIs->setText(QString::number(sgwSettings.ldi));
    this->ui->tet_sgw_apn_lists->setText(sgwSettings.apnList);
}
void SgwForm::loadAndSpawn(const SgwSettings &sgwSettings, const QString &projectName,bool enable){
    this->sgwSettings = sgwSettings;
    this->projectName = projectName;
    this->updateUi();
    this->setReadOnly(enable);
    this->show();
}
void SgwForm::setReadOnly(bool value)
{
    this->ui->tet_sgw_apn_lists->setReadOnly(value);
    this->ui->tet_sgw_ipAddresses->setReadOnly(value);
    this->ui->tet_sgw_LDIs->setReadOnly(value);
    this->ui->tet_sgw_names->setReadOnly(value);
    this->ui->pbReset->setEnabled(!value);
}
