#include "sgwform.h"
#include "ui_sgwform.h"
#include <Maps/Parameters/MapWindow/mapwindow.h>
#include <Maps/Parameters/MapWindow/mapwindowlarge.h>
extern MapWindow *map_w;
extern MapWindowLarge *map_wl;
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

void SGWForm::setParameters(Sgw *sgw)
{
    this->sgw = sgw;
    ui->tet_sgw_names->setText(sgw->getNames().trimmed());
    ui->tet_sgw_ipAddresses->setText(sgw->getIpAddresses().trimmed());
    ui->tet_sgw_apn_lists->setText(sgw->getApnLists().trimmed());
    ui->tet_sgw_LDIs->setText(sgw->getLDIs().trimmed());

    ui->gbSGW->setEnabled(sgw->getCore_network_gateway());
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
{
    if(flagConfirmNewValue && (ui->tet_sgw_names->text() != sgw->getNames())){
         sgw->setNames(ui->tet_sgw_names->text());
         wasThereChanges=true;
         msg.setText("Name: "+ sgw->getNames() );
         msg.exec();
    }
    sgw->setNames(ui->tet_sgw_names->text());
}

void SGWForm::on_tet_sgw_ipAddresses_returnPressed()
{
    if(flagConfirmNewValue && (ui->tet_sgw_ipAddresses->text() != sgw->getIpAddresses())){
        sgw->setIpAddresses(ui->tet_sgw_ipAddresses->text());
        wasThereChanges=true;
        msg.setText("IpAddresses: "+ sgw->getIpAddresses());
        msg.exec();
    }
    sgw->setIpAddresses(ui->tet_sgw_ipAddresses->text());
}

void SGWForm::on_tet_sgw_apn_lists_returnPressed()
{
    if(flagConfirmNewValue && (ui->tet_sgw_apn_lists->text()!= sgw->getApnLists())){
        sgw->setApn_lists(ui->tet_sgw_apn_lists->text());
        wasThereChanges=true;
        msg.setText("Apn_lists: "+sgw->getApnLists() );
        msg.exec();
    }
    sgw->setApn_lists(ui->tet_sgw_apn_lists->text());
}

void SGWForm::on_tet_sgw_LDIs_returnPressed()
{
     if(flagConfirmNewValue && (ui->tet_sgw_LDIs->text() != sgw->getLDIs())){
         sgw->setLDIs(ui->tet_sgw_LDIs->text());
         wasThereChanges=true;
         msg.setText("LDIs: "+ sgw->getLDIs());
         msg.exec();
     }
    sgw->setLDIs(ui->tet_sgw_LDIs->text());
}

void SGWForm::on_buttonBox_accepted()
{
    if(wasChangesBeforeAccept())
        setChanges();
    msg.setText("Changes has been succesfully approved ");
    if(flagConfirmNewValue && checkboxactive && wasThereChanges)
        msg.exec();
    this->close();
    wasThereChanges=false;
}

void SGWForm::saveAll()
{
    sgw->setNames(ui->tet_sgw_names->text());
    sgw->setIpAddresses(ui->tet_sgw_ipAddresses->text());
    sgw->setApn_lists(ui->tet_sgw_apn_lists->text());
    sgw->setLDIs(ui->tet_sgw_LDIs->text());
}

void SGWForm::on_pbReset_clicked()
{

    sgw->resetParams();
    setParameters(sgw);
    if(map_w!=NULL)
        map_w->resetFlags();
    else if (map_wl!=NULL)
        map_wl->resetFlags();

    if(checkboxactive){
        sgw->resetParams();
        setParameters(sgw);
        map_w->resetFlags();
    }
}

void SGWForm::on_buttonBox_rejected()
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
         // this part should never work
         break;
                }
    }else
    {
        this->close();
    }
    wasThereChanges=false;
}

bool SGWForm::wasChangesBeforeAccept()
{
    if(ui->tet_sgw_names->text() != sgw->getNames())
    {
        wasThereChanges=true;
        return true;
    }else if(ui->tet_sgw_ipAddresses->text() != sgw->getIpAddresses())
    {
        wasThereChanges=true;
        return true;
    }else if(ui->tet_sgw_apn_lists->text()!= sgw->getApnLists())
    {
        wasThereChanges=true;
        return true;
    }else if(ui->tet_sgw_LDIs->text() != sgw->getLDIs())
    {
            wasThereChanges=true;
            return true;
    }else
    {
        return false;
    }
}

void SGWForm::setChanges()
{
    if(ui->tet_sgw_names->text() != sgw->getNames())
    {
        sgw->setNames(ui->tet_sgw_names->text());
    }
    if(ui->tet_sgw_ipAddresses->text() != sgw->getIpAddresses())
    {
        sgw->setIpAddresses(ui->tet_sgw_ipAddresses->text());
    }
    if(ui->tet_sgw_apn_lists->text()!= sgw->getApnLists())
    {
        sgw->setApn_lists(ui->tet_sgw_apn_lists->text());
    }else if(ui->tet_sgw_LDIs->text() != sgw->getLDIs())
    {
        sgw->setLDIs(ui->tet_sgw_LDIs->text());
    }


}
