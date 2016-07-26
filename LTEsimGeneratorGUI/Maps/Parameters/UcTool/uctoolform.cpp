#include "uctoolform.h"
#include "ui_uctoolform.h"
#include <QtDebug>


UCtoolForm::UCtoolForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UCtoolForm)
{
    ui->setupUi(this);
    flagConfirmNewValue = true;
    wasThereChanges=false;
    this->setWindowTitle("UCtool settings");
    this->ui->lblSgw_names->setToolTip("UCTOOL device name the IP address of the UCtool e.g. \"uctool1;192.168.3.5\"");
    this->ui->lblSgw_ipAddresses->setToolTip("UCTOOL device name and cell names used to map e.g. \"uctool1;cell11,cell12\" ");
    this->ui->lblSgw_apn_list->setToolTip("UCTOOL device name and the IP address of the service requested \"uctool1;192.168.3.19\" ");
}

void UCtoolForm::set_checkboxactive(bool check)
{
    checkboxactive=check;
}

bool UCtoolForm::get_checkboxactive()
{
    return  checkboxactive;
}

UCtoolForm::~UCtoolForm()
{
    delete ui;
}

void UCtoolForm::setParameters(Ue *ue)
{
    this->ue = ue;
    ui->tet_uctool_cIds->setText(ue->getUctool_cIds());
    ui->tet_uctool_ip->setText(ue->getUctool_ip());
    ui->tet_uctool_service_ip->setText(ue->getUctool_service_ip());

    ui->gbUCtool->setEnabled(ue->getStart_ue_component());              //check flag Strat UE componet
}

void UCtoolForm::on_tet_uctool_ip_returnPressed()
{
    if(flagConfirmNewValue && (ui->tet_uctool_ip->text() != ue->getUctool_ip())){
        ue->setUctool_ip(ui->tet_uctool_ip->text());
        wasThereChanges=true;
        msg.setText("You set tet_uctool_ip: " + ue->getUctool_ip());
        msg.exec();
    }else
    ue->setUctool_ip(ui->tet_uctool_ip->text());
}

void UCtoolForm::on_tet_uctool_cIds_returnPressed()
{
    if(flagConfirmNewValue && (ui->tet_uctool_cIds->text() != ue->getUctool_cIds())){
        ue->setUctool_cIds(ui->tet_uctool_cIds->text());
        wasThereChanges=true;
        msg.setText("You set tet_uctool_cIds: "+ ue->getUctool_cIds());
        msg.exec();
    }else
    ue->setUctool_cIds(ui->tet_uctool_cIds->text());
}

void UCtoolForm::on_tet_uctool_service_ip_returnPressed()
{
    if(flagConfirmNewValue && (ui->tet_uctool_service_ip->text()!= ue->getUctool_service_ip())){
        ue->setUctool_service_ip(ui->tet_uctool_service_ip->text());
        wasThereChanges=true;
        msg.setText("You set uctool_service_ip: "+ ue->getUctool_service_ip());
        msg.exec();
    }else
    ue->setUctool_service_ip(ui->tet_uctool_service_ip->text());
}

void UCtoolForm::on_buttonBox_accepted()
{

    this->close();
   if(wasChangesBeforeAccept())
       setChanges();
    msg.setText(" Changes has been succesfully approved ");
    if(flagConfirmNewValue && wasThereChanges)
        msg.exec();
    wasThereChanges=false;
}

void UCtoolForm::on_buttonBox_rejected()
{
    if(wasChangesBeforeAccept())
    {
        msgBox.setWindowTitle("Warning");
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setText(trUtf8(("File was changed")));
        msgBox.setInformativeText(trUtf8("Do you want to save changes?"));
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);

    int ret = msgBox.exec();

    switch (ret) {
      case QMessageBox::Save:
           setChanges();
           this->close();
         break;
      case QMessageBox::Discard:
            this->close();
         break;
      case QMessageBox::Cancel:
           msgBox.close();
         break;
      default:

         break;
                }
    }else
    {
        this->close();
    }
    wasThereChanges=false;

}

void UCtoolForm::on_pbReset_clicked()
{
    if(checkboxactive){
        ue->resetParamsUCTOOL();
        setParameters(ue);
    }
    wasThereChanges=false;
}

bool UCtoolForm::wasChangesBeforeAccept()
{
    if(ui->tet_uctool_ip->text()!= ue->getUctool_ip())
    {
        wasThereChanges=true;
        return true;
    }else if(ui->tet_uctool_cIds->text()!= ue->getUctool_cIds())
    {
        wasThereChanges=true;
        return true;
    }else if(ui->tet_uctool_service_ip->text()!= ue->getUctool_service_ip())
    {
        wasThereChanges=true;
        return true;
    }else
    {
    return false;
    }
}

void UCtoolForm::setChanges()
{
    if(ui->tet_uctool_ip->text()!= ue->getUctool_ip())
    {
        ue->setUctool_ip(ui->tet_uctool_ip->text());
    }
    if(ui->tet_uctool_cIds->text()!= ue->getUctool_cIds())
    {
        ue->setUctool_cIds(ui->tet_uctool_cIds->text());
    }
    if(ui->tet_uctool_service_ip->text()!= ue->getUctool_service_ip())
    {
        ue->setUctool_service_ip(ui->tet_uctool_service_ip->text());
    }

}
