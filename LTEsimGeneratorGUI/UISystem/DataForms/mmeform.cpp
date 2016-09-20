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

void MmeForm::updateUi()
{
    QString names;
    for (int i=0;i<mmeSettings.names.size();i++){
        names.append(mmeSettings.names[i]);
        if (i!=mmeSettings.names.size()-1){
            names.append(", ");
        }
    }
    this->ui->tetMme_names->setText(names);
    this->ui->tetMme_tais->setText(mmeSettings.tais);
    this->ui->tetMme_s1ap_uris->setText(mmeSettings.uris);
    this->ui->tetS1ap_pluginFilterPath->setText(mmeSettings.pluginFilterPath);
    this->update();
    this->ui->checkBox->setChecked(mmeSettings.simulatedCoreNetwork);
    enableWindow(this->mmeSettings.simulatedCoreNetwork);
}
void MmeForm::loadAndSpawn(const MmeSettings &mmeSettings, const QString &projectName, bool enable){
    this->mmeSettings=mmeSettings;
    this->projectName=projectName;
    this->updateUi();
    this->ui->checkBox->setEnabled(!enable);
    this->setEnabled(!enable);
    this->show();
}


void MmeForm::on_buttonBox_accepted()
{
    setMmeChanges();
    emit updateMme(mmeSettings,projectName);
    this->close();
}


void MmeForm::on_buttonBox_rejected()
{
    this->close();
}


void MmeForm::on_pbReset_clicked()
{
    updateUi();
}

void MmeForm::setMmeChanges(){

    mmeSettings.names = this->ui->tetMme_names->text().split(",");
    mmeSettings.tais=this->ui->tetMme_tais->text();
    mmeSettings.uris=this->ui->tetMme_s1ap_uris->text();
    mmeSettings.pluginFilterPath=this->ui->tetS1ap_pluginFilterPath->text();
    mmeSettings.simulatedCoreNetwork = this->ui->checkBox->isChecked();
    emit updateMme(mmeSettings,projectName);
}
void MmeForm::setReadOnly(bool value)
{
    this->ui->tetMmes->setReadOnly(value);
    this->ui->tetMme_names->setReadOnly(value);
    this->ui->tetMme_s1ap_uris->setReadOnly(value);
    this->ui->tetMme_tais->setReadOnly(value);
    this->ui->tetS1ap_pluginFilterPath->setReadOnly(value);
    this->ui->checkBox->setCheckable(!value);
    this->ui->pbReset->setEnabled(!value);
}
void MmeForm::enableWindow(bool value)
{
    this->ui->tetMmes->setEnabled(value);
    this->ui->tetMme_names->setEnabled(value);
    this->ui->tetMme_s1ap_uris->setEnabled(value);
    this->ui->tetMme_tais->setEnabled(value);
    this->ui->tetS1ap_pluginFilterPath->setEnabled(value);
    this->ui->pbReset->setEnabled(value);
}

void MmeForm::on_checkBox_toggled(bool checked)
{
    mmeSettings.simulatedCoreNetwork=checked;
    updateUi();
}
