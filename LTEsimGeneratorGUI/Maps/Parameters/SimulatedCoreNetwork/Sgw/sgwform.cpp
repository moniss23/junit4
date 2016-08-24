#include "sgwform.h"
#include "ui_sgwform.h"
#include <Maps/Parameters/MapWindow/mapwindow.h>
#include <QRegExp>
#include <QPair>
extern MapWindow *map_w;
SGWForm::SGWForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SGWForm)
{
    ui->setupUi(this);
    flagConfirmNewValue = true;
    wasThereChanges=false;
    this->setWindowTitle("SGW settings");
    //set tooltips for lbls
    this->ui->lblSgw_names->setToolTip("Name of the Serving GWs e.g. \"sgw1\"");
    this->ui->lblSgw_ipAddresses->setToolTip("e.g. \"127.0.0.1\" ");
    this->ui->lblSgw_apn_list->setToolTip("The parameter contains APN name and an IP number range tjat the SGW will assign to the UE e.g. \"ltesim-core-network,172.17.0.1/16;\"");
    this->ui->lblSgw_LDIs->setToolTip("e.g. \"30\"");
}


void SGWForm::set_checkboxactive(bool check)
{
    checkboxactive=check;
}

bool SGWForm::get_checkboxactive()
{
    return  checkboxactive;
}


SGWForm::~SGWForm()
{
    delete ui;
}

void SGWForm::on_tet_sgw_names_returnPressed()
{/*
    if(flagConfirmNewValue && (ui->tet_sgw_names->text() != sgw->getNames())){
         sgw->setNames(ui->tet_sgw_names->text());
         wasThereChanges=true;
         msg.setText("Name: "+ sgw->getNames() );
         msg.exec();
    }
    sgw->setNames(ui->tet_sgw_names->text());
    */
}

void SGWForm::on_tet_sgw_ipAddresses_returnPressed()
{/*
    if(flagConfirmNewValue && (ui->tet_sgw_ipAddresses->text() != sgw->getIpAddresses())){
        sgw->setIpAddresses(ui->tet_sgw_ipAddresses->text());
        wasThereChanges=true;
        msg.setText("IpAddresses: "+ sgw->getIpAddresses());
        msg.exec();
    }
    sgw->setIpAddresses(ui->tet_sgw_ipAddresses->text());
*/
}

void SGWForm::on_tet_sgw_apn_lists_returnPressed()
{/*
    if(flagConfirmNewValue && (ui->tet_sgw_apn_lists->text()!= sgw->getApnLists())){
        sgw->setApn_lists(ui->tet_sgw_apn_lists->text());
        wasThereChanges=true;
        msg.setText("Apn_lists: "+sgw->getApnLists() );
        msg.exec();
    }
    sgw->setApn_lists(ui->tet_sgw_apn_lists->text());
    */
}

void SGWForm::on_tet_sgw_LDIs_returnPressed()
{/*
     if(flagConfirmNewValue && (ui->tet_sgw_LDIs->text() != sgw->getLDIs())){
         sgw->setLDIs(ui->tet_sgw_LDIs->text());
         wasThereChanges=true;
         msg.setText("LDIs: "+ sgw->getLDIs());
         msg.exec();
     }
    sgw->setLDIs(ui->tet_sgw_LDIs->text());
    */
}

void SGWForm::on_buttonBox_accepted()
{
    setChanges();
    msg.setText("Changes has been succesfully approved ");
    msg.exec();
    this->close();
}
void SGWForm::on_buttonBox_rejected(){
    this->close();
}

void SGWForm::on_pbReset_clicked()
{
}

void SGWForm::setChanges()
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
        sgwSettings.apnList.append(QPair<QString,QString>(apnListToSave[i],apnListToSave[i+1]));
    }
    emit updateSgw(sgwSettings,projectName);
}
void SGWForm::setDefaultParameters(){
    this->ui->tet_sgw_names->setText(sgwSettings.name);
    this->ui->tet_sgw_ipAddresses->setText(sgwSettings.ipAdress);
    this->ui->tet_sgw_LDIs->setText(QString::number(sgwSettings.ldi));
    for (int i=0;i<sgwSettings.apnList.size();i++){
        this->ui->tet_sgw_apn_lists->setText(this->ui->tet_sgw_apn_lists->text()+sgwSettings.apnList[i].first+":"+sgwSettings.apnList[i].second+",");
    }
}

void SGWForm::loadAndSpawn(const SgwSettings &sgwSettings, const QString &projectName){
    this->sgwSettings = sgwSettings;
    this->projectName = projectName;
    this->setDefaultParameters();
    this->show();
}
