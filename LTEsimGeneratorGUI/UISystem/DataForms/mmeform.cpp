#include "mmeform.h"
#include "ui_mmeform.h"

MmeForm::MmeForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MmeForm)
{
    ui->setupUi(this);
    this->setWindowTitle("MME settings");
    this->ui->lblMme_names->setToolTip("Name of the MME component e.g. \"mme1\"");
    this->ui->lblMme_tais->setToolTip("MME tracking area identity value e.g. \"62F2281200\"");
    this->ui->lblMmes->setToolTip("Number of MMEs (used in multiple MME configuration) ");
    this->ui->lblMme_s1ap_uris->setToolTip("The IP addresses must be available on the LTEsim server and reachable from the eNB CP interface e.g.\"sctp://127.0.0.1:36412\"");
    this->ui->lbl_Mme_s1ap_pluginFilterPath->setToolTip("Set the filter path e.g. \"/etc/alternatives/ltesim-root/ltesim/internal\"");
  }


MmeForm::~MmeForm()
{
    delete ui;
}

void MmeForm::setDefaultParameters()
{
    QString names;
    for (int i=0;i<mmeSettings.names.size();i++){
        names.append(mmeSettings.names[i]);
        names.append(", ");
    }
    this->ui->tetMme_names->setText(names);
    this->ui->tetMme_tais->setText(mmeSettings.tais);
    this->ui->tetMme_s1ap_uris->setText(mmeSettings.uris);
    this->ui->tetS1ap_pluginFilterPath->setText(mmeSettings.pluginFilterPath);

}
void MmeForm::loadAndSpawn(const MmeSettings &mmeSettings, const QString &projectName){
    this->mmeSettings=mmeSettings;
    this->projectName=projectName;
    this->setDefaultParameters();
    this->show();
}


void MmeForm::on_buttonBox_accepted()
{
    setMmeChanges();
    this->close();
}


void MmeForm::on_buttonBox_rejected()
{
    this->close();
}


void MmeForm::on_pbReset_clicked()
{
    setDefaultParameters();
}

void MmeForm::setMmeChanges(){

    mmeSettings.names = this->ui->tetMme_names->text().split(",");
    mmeSettings.tais=this->ui->tetMme_tais->text();
    mmeSettings.uris=this->ui->tetMme_s1ap_uris->text();
    mmeSettings.pluginFilterPath=this->ui->tetS1ap_pluginFilterPath->text();
    emit updateMme(mmeSettings,projectName);
}

