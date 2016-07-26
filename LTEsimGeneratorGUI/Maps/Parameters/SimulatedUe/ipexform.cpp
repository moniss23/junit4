#include "ipexform.h"
#include "ui_ipexform.h"

ipexForm::ipexForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ipexForm)
{
    ui->setupUi(this);
    flagConfirmNewValue = true;
    wasThereChanges=false;
    this->ui->label_4->setToolTip("Use local IPGWTG e.g. \"ipgwtg\"");
    this->ui->label->setToolTip("Configuration of the ipgwtg user data generator e.g: \n  \" ipex.isp.sip.offset = 31000 \"  \n \" ipex.isp.qci1.port    = 31010 \" \n  \" ipex.isp.qci2.port    = 31020 \" \n  \" ipex.isp.qci5.port    = 31050 \" ");
    this->ui->label_2->setToolTip("IP address of the interface that can reach the PGW e.g. \"10.10.0.1\"   ");
    this->ui->label_3->setToolTip("Port name e.g. \"21000\"");
}

void ipexForm::set_checkboxactive(bool check)
{
    checkboxactive=check;
}

bool ipexForm::get_checkboxactive()
{
    return  checkboxactive;
}

ipexForm::~ipexForm()
{
    delete ui;
}

void ipexForm::setParameters(Ipgwtg *ipex, bool flagUe)
{
    this->ipex = ipex;
    this->flagUe = flagUe;
    ui->gbIpex->setEnabled(flagUe);
    ui->tet_dataGenerator->setText(ipex->getDataGenerator());
    ui->tet_userDataGen->setText(ipex->getUserDataGen());
    ui->tet_ipgwtg_ipAddress->setText(ipex->getIpgwtg_ipAddress());
    ui->tet_ipgwtg_port->setText(ipex->getIpgwtg_port());

    ui->checkBox_ipgwtg_ftp_sender_connect_put->setChecked(ipex->getIpgwtg_ftp_sender_connect_put());
    ui->checkBox_ipgwtg_inband_signaling->setChecked(ipex->getIpgwtg_inband_signaling());
    ui->checkBox_start_isp_simulator->setChecked(ipex->getStart_isp_simulator());

}

void ipexForm::on_tet_ipgwtg_ipAddress_returnPressed()
{
    if(flagConfirmNewValue && (ui->tet_ipgwtg_ipAddress->text() != ipex->getIpgwtg_ipAddress())){
        ipex->setIpgwtg_ipAddress(ui->tet_ipgwtg_ipAddress->text());
        wasThereChanges=true;
        msg.setText("You set Ipgwtg_ipAddress: " + ipex->getIpgwtg_ipAddress());
        msg.exec();
      }else
      ipex->setIpgwtg_ipAddress(ui->tet_ipgwtg_ipAddress->text());
}

void ipexForm::on_tet_ipgwtg_port_returnPressed()
{
    if(flagConfirmNewValue && (ui->tet_ipgwtg_port->text()!= ipex->getIpgwtg_port())){
        ipex->setIpgwtg_port(ui->tet_ipgwtg_port->text());
        wasThereChanges=true;
        msg.setText("You set Ipgwtg_port: " + ipex->getIpgwtg_port());
        msg.exec();
    }else
         ipex->setIpgwtg_port(ui->tet_ipgwtg_port->text());
}

void ipexForm::on_checkBox_start_isp_simulator_clicked()
{
    ipex->setIpgwtg_ftp_sender_connect_put(ui->checkBox_ipgwtg_ftp_sender_connect_put->isChecked());
}

void ipexForm::on_checkBox_ipgwtg_inband_signaling_clicked()
{
    ipex->setIpgwtg_inband_signaling(ui->checkBox_ipgwtg_inband_signaling->isChecked());
}

void ipexForm::on_checkBox_ipgwtg_ftp_sender_connect_put_clicked()
{
    ipex->setStart_isp_simulator(ui->checkBox_start_isp_simulator->isChecked());
}

void ipexForm::on_buttonBox_accepted()
{
    this->window()->close();

    if(wasChangesBeforeAccept())
        setChanges();
    msg.setText("Changes has been succesfully approved");
    if(flagConfirmNewValue && wasThereChanges)
        msg.exec();
     wasThereChanges=false;
}

void ipexForm::on_buttonBox_rejected()
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
        this->close(); //Window()
    }
    wasThereChanges=false;

}

void ipexForm::on_pbReset_clicked()
{
    if(checkboxactive){
        ipex->resetParams();
        setParameters(ipex, flagUe);
    }
    wasThereChanges=false;
}


void ipexForm::on_tet_dataGenerator_returnPressed()
{
    if(flagConfirmNewValue && (ui->tet_dataGenerator->text()!= ipex->getDataGenerator())){
        ipex->setDataGenerator(ui->tet_dataGenerator->text());
        wasThereChanges=true;
        msg.setText("You set dataGenerator: " + ipex->getDataGenerator());
        msg.exec();
    }else
        ipex->setDataGenerator(ui->tet_dataGenerator->text());
}

void ipexForm::saveAll()
{
    ipex->setUserDataGen(ui->tet_userDataGen->toPlainText());
    ipex->setIpgwtg_ftp_sender_connect_put(ui->checkBox_ipgwtg_ftp_sender_connect_put->isChecked());
    ipex->setIpgwtg_inband_signaling(ui->checkBox_ipgwtg_inband_signaling->isChecked());
    ipex->setStart_isp_simulator(ui->checkBox_start_isp_simulator->isChecked());
    ipex->setDataGenerator(ui->tet_dataGenerator->text());
}

    bool ipexForm::wasChangesBeforeAccept()
    {
       if(ui->tet_ipgwtg_ipAddress->text() != ipex->getIpgwtg_ipAddress())
       {
             wasThereChanges=true;
             return true;
       }else if (ui->tet_ipgwtg_port->text()!= ipex->getIpgwtg_port())
       {
           wasThereChanges=true;
           return true;
       }else if (ui->tet_dataGenerator->text()!= ipex->getDataGenerator())
       {
           wasThereChanges=true;
           return true;
       }else
       {
           return false;
       }
    }

    void ipexForm::setChanges()
    {
        if(ui->tet_ipgwtg_ipAddress->text() != ipex->getIpgwtg_ipAddress())
        {
            ipex->setIpgwtg_ipAddress(ui->tet_ipgwtg_ipAddress->text());
        }
        if (ui->tet_ipgwtg_port->text()!= ipex->getIpgwtg_port())
        {
            ipex->setIpgwtg_port(ui->tet_ipgwtg_port->text());
        }
        if (ui->tet_dataGenerator->text()!= ipex->getDataGenerator())
        {
            ipex->setDataGenerator(ui->tet_dataGenerator->text());
        }
        saveAll();

    }


